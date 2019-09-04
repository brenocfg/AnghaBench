#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
struct machine {int dummy; } ;
struct dso_cache {int offset; int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {scalar_t__ fd; int /*<<< orphan*/  status; } ;
struct dso {TYPE_1__ data; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DSO_DATA_STATUS_ERROR ; 
 int DSO__DATA_CACHE_MASK ; 
 scalar_t__ DSO__DATA_CACHE_SIZE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  dso__data_open_lock ; 
 struct dso_cache* dso_cache__insert (struct dso*,struct dso_cache*) ; 
 int /*<<< orphan*/  dso_cache__memcpy (struct dso_cache*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (struct dso_cache*) ; 
 int /*<<< orphan*/  pread (scalar_t__,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_to_open_dso (struct dso*,struct machine*) ; 
 struct dso_cache* zalloc (scalar_t__) ; 

__attribute__((used)) static ssize_t
dso_cache__read(struct dso *dso, struct machine *machine,
		u64 offset, u8 *data, ssize_t size)
{
	struct dso_cache *cache;
	struct dso_cache *old;
	ssize_t ret;

	do {
		u64 cache_offset;

		cache = zalloc(sizeof(*cache) + DSO__DATA_CACHE_SIZE);
		if (!cache)
			return -ENOMEM;

		pthread_mutex_lock(&dso__data_open_lock);

		/*
		 * dso->data.fd might be closed if other thread opened another
		 * file (dso) due to open file limit (RLIMIT_NOFILE).
		 */
		try_to_open_dso(dso, machine);

		if (dso->data.fd < 0) {
			ret = -errno;
			dso->data.status = DSO_DATA_STATUS_ERROR;
			break;
		}

		cache_offset = offset & DSO__DATA_CACHE_MASK;

		ret = pread(dso->data.fd, cache->data, DSO__DATA_CACHE_SIZE, cache_offset);
		if (ret <= 0)
			break;

		cache->offset = cache_offset;
		cache->size   = ret;
	} while (0);

	pthread_mutex_unlock(&dso__data_open_lock);

	if (ret > 0) {
		old = dso_cache__insert(dso, cache);
		if (old) {
			/* we lose the race */
			free(cache);
			cache = old;
		}

		ret = dso_cache__memcpy(cache, offset, data, size);
	}

	if (ret <= 0)
		free(cache);

	return ret;
}