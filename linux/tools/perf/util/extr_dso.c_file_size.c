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
struct stat {int /*<<< orphan*/  st_size; } ;
struct machine {int dummy; } ;
struct TYPE_2__ {scalar_t__ fd; int /*<<< orphan*/  file_size; void* status; } ;
struct dso {TYPE_1__ data; } ;
typedef  int /*<<< orphan*/  sbuf ;

/* Variables and functions */
 void* DSO_DATA_STATUS_ERROR ; 
 int STRERR_BUFSIZE ; 
 int /*<<< orphan*/  dso__data_open_lock ; 
 int errno ; 
 scalar_t__ fstat (scalar_t__,struct stat*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  str_error_r (int,char*,int) ; 
 int /*<<< orphan*/  try_to_open_dso (struct dso*,struct machine*) ; 

__attribute__((used)) static int file_size(struct dso *dso, struct machine *machine)
{
	int ret = 0;
	struct stat st;
	char sbuf[STRERR_BUFSIZE];

	pthread_mutex_lock(&dso__data_open_lock);

	/*
	 * dso->data.fd might be closed if other thread opened another
	 * file (dso) due to open file limit (RLIMIT_NOFILE).
	 */
	try_to_open_dso(dso, machine);

	if (dso->data.fd < 0) {
		ret = -errno;
		dso->data.status = DSO_DATA_STATUS_ERROR;
		goto out;
	}

	if (fstat(dso->data.fd, &st) < 0) {
		ret = -errno;
		pr_err("dso cache fstat failed: %s\n",
		       str_error_r(errno, sbuf, sizeof(sbuf)));
		dso->data.status = DSO_DATA_STATUS_ERROR;
		goto out;
	}
	dso->data.file_size = st.st_size;

out:
	pthread_mutex_unlock(&dso__data_open_lock);
	return ret;
}