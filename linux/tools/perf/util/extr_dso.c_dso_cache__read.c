#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
struct machine {int dummy; } ;
struct dso_cache {int offset; scalar_t__ size; int /*<<< orphan*/  data; } ;
struct dso {scalar_t__ binary_type; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ DSO_BINARY_TYPE__BPF_PROG_INFO ; 
 int DSO__DATA_CACHE_MASK ; 
 scalar_t__ DSO__DATA_CACHE_SIZE ; 
 scalar_t__ ENOMEM ; 
 scalar_t__ bpf_read (struct dso*,int,int /*<<< orphan*/ ) ; 
 struct dso_cache* dso_cache__insert (struct dso*,struct dso_cache*) ; 
 scalar_t__ dso_cache__memcpy (struct dso_cache*,int,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ file_read (struct dso*,struct machine*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct dso_cache*) ; 
 struct dso_cache* zalloc (scalar_t__) ; 

__attribute__((used)) static ssize_t
dso_cache__read(struct dso *dso, struct machine *machine,
		u64 offset, u8 *data, ssize_t size)
{
	u64 cache_offset = offset & DSO__DATA_CACHE_MASK;
	struct dso_cache *cache;
	struct dso_cache *old;
	ssize_t ret;

	cache = zalloc(sizeof(*cache) + DSO__DATA_CACHE_SIZE);
	if (!cache)
		return -ENOMEM;

	if (dso->binary_type == DSO_BINARY_TYPE__BPF_PROG_INFO)
		ret = bpf_read(dso, cache_offset, cache->data);
	else
		ret = file_read(dso, machine, cache_offset, cache->data);

	if (ret > 0) {
		cache->offset = cache_offset;
		cache->size   = ret;

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