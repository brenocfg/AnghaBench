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
struct scsi_cmnd {int dummy; } ;

/* Variables and functions */
 int SDEBUG_OPT_MAC_TIMEOUT ; 
 int SDEBUG_OPT_TIMEOUT ; 
 int abs (int) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ scsi_medium_access_command (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  sdebug_cmnd_count ; 
 int sdebug_every_nth ; 
 int sdebug_opts ; 

__attribute__((used)) static bool fake_timeout(struct scsi_cmnd *scp)
{
	if (0 == (atomic_read(&sdebug_cmnd_count) % abs(sdebug_every_nth))) {
		if (sdebug_every_nth < -1)
			sdebug_every_nth = -1;
		if (SDEBUG_OPT_TIMEOUT & sdebug_opts)
			return true; /* ignore command causing timeout */
		else if (SDEBUG_OPT_MAC_TIMEOUT & sdebug_opts &&
			 scsi_medium_access_command(scp))
			return true; /* time out reads and writes */
	}
	return false;
}