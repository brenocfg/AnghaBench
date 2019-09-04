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
struct fsg_lun {int /*<<< orphan*/  sense_data; } ;
struct fsg_common {struct fsg_lun* curlun; } ;

/* Variables and functions */
 int /*<<< orphan*/  SS_WRITE_ERROR ; 
 int fsg_lun_fsync_sub (struct fsg_lun*) ; 

__attribute__((used)) static int do_synchronize_cache(struct fsg_common *common)
{
	struct fsg_lun	*curlun = common->curlun;
	int		rc;

	/* We ignore the requested LBA and write out all file's
	 * dirty data buffers. */
	rc = fsg_lun_fsync_sub(curlun);
	if (rc)
		curlun->sense_data = SS_WRITE_ERROR;
	return 0;
}