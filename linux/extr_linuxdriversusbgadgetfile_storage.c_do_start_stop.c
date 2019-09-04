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
struct fsg_lun {int /*<<< orphan*/  sense_data; } ;
struct fsg_dev {int* cmnd; struct fsg_lun* curlun; } ;
struct TYPE_2__ {int /*<<< orphan*/  removable; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SS_INVALID_COMMAND ; 
 TYPE_1__ mod_data ; 

__attribute__((used)) static int do_start_stop(struct fsg_dev *fsg)
{
	struct fsg_lun	*curlun = fsg->curlun;
	int		loej, start;

	if (!mod_data.removable) {
		curlun->sense_data = SS_INVALID_COMMAND;
		return -EINVAL;
	}

	// int immed = fsg->cmnd[1] & 0x01;
	loej = fsg->cmnd[4] & 0x02;
	start = fsg->cmnd[4] & 0x01;

#ifdef CONFIG_USB_FILE_STORAGE_TEST
	if ((fsg->cmnd[1] & ~0x01) != 0 ||		// Mask away Immed
			(fsg->cmnd[4] & ~0x03) != 0) {	// Mask LoEj, Start
		curlun->sense_data = SS_INVALID_FIELD_IN_CDB;
		return -EINVAL;
	}

	if (!start) {

		/* Are we allowed to unload the media? */
		if (curlun->prevent_medium_removal) {
			LDBG(curlun, "unload attempt prevented\n");
			curlun->sense_data = SS_MEDIUM_REMOVAL_PREVENTED;
			return -EINVAL;
		}
		if (loej) {		// Simulate an unload/eject
			up_read(&fsg->filesem);
			down_write(&fsg->filesem);
			fsg_lun_close(curlun);
			up_write(&fsg->filesem);
			down_read(&fsg->filesem);
		}
	} else {

		/* Our emulation doesn't support mounting; the medium is
		 * available for use as soon as it is loaded. */
		if (!fsg_lun_is_open(curlun)) {
			curlun->sense_data = SS_MEDIUM_NOT_PRESENT;
			return -EINVAL;
		}
	}
#endif
	return 0;
}