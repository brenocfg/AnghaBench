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
typedef  int /*<<< orphan*/  u64 ;
struct machine {int dummy; } ;
struct TYPE_2__ {scalar_t__ fd; int /*<<< orphan*/  status; } ;
struct dso {TYPE_1__ data; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DSO_DATA_STATUS_ERROR ; 
 int /*<<< orphan*/  DSO__DATA_CACHE_SIZE ; 
 int /*<<< orphan*/  dso__data_open_lock ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  pread (scalar_t__,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_to_open_dso (struct dso*,struct machine*) ; 

__attribute__((used)) static ssize_t file_read(struct dso *dso, struct machine *machine,
			 u64 offset, char *data)
{
	ssize_t ret;

	pthread_mutex_lock(&dso__data_open_lock);

	/*
	 * dso->data.fd might be closed if other thread opened another
	 * file (dso) due to open file limit (RLIMIT_NOFILE).
	 */
	try_to_open_dso(dso, machine);

	if (dso->data.fd < 0) {
		dso->data.status = DSO_DATA_STATUS_ERROR;
		ret = -errno;
		goto out;
	}

	ret = pread(dso->data.fd, data, DSO__DATA_CACHE_SIZE, offset);
out:
	pthread_mutex_unlock(&dso__data_open_lock);
	return ret;
}