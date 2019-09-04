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
struct rw_semaphore {int dummy; } ;
struct fsg_lun {int cdrom; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int _fsg_store_ro (struct fsg_lun*,int) ; 
 int /*<<< orphan*/  down_read (struct rw_semaphore*) ; 
 int strtobool (char const*,int*) ; 
 int /*<<< orphan*/  up_read (struct rw_semaphore*) ; 

ssize_t fsg_store_cdrom(struct fsg_lun *curlun, struct rw_semaphore *filesem,
			const char *buf, size_t count)
{
	bool		cdrom;
	int		ret;

	ret = strtobool(buf, &cdrom);
	if (ret)
		return ret;

	down_read(filesem);
	ret = cdrom ? _fsg_store_ro(curlun, true) : 0;

	if (!ret) {
		curlun->cdrom = cdrom;
		ret = count;
	}
	up_read(filesem);

	return ret;
}