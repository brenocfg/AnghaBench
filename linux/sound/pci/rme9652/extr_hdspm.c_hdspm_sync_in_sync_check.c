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
struct hdspm {int io_type; } ;

/* Variables and functions */
#define  AES32 132 
#define  AIO 131 
 int /*<<< orphan*/  HDSPM_RD_STATUS_3 ; 
 int /*<<< orphan*/  HDSPM_statusRegister ; 
 int /*<<< orphan*/  HDSPM_statusRegister2 ; 
 int HDSPM_syncInLock ; 
 int HDSPM_syncInSync ; 
#define  MADI 130 
#define  MADIface 129 
#define  RayDAT 128 
 int hdspm_read (struct hdspm*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hdspm_sync_in_sync_check(struct hdspm *hdspm)
{
	int status, lock = 0, sync = 0;

	switch (hdspm->io_type) {
	case RayDAT:
	case AIO:
		status = hdspm_read(hdspm, HDSPM_RD_STATUS_3);
		lock = (status & 0x400) ? 1 : 0;
		sync = (status & 0x800) ? 1 : 0;
		break;

	case MADI:
		status = hdspm_read(hdspm, HDSPM_statusRegister);
		lock = (status & HDSPM_syncInLock) ? 1 : 0;
		sync = (status & HDSPM_syncInSync) ? 1 : 0;
		break;

	case AES32:
		status = hdspm_read(hdspm, HDSPM_statusRegister2);
		lock = (status & 0x100000) ? 1 : 0;
		sync = (status & 0x200000) ? 1 : 0;
		break;

	case MADIface:
		break;
	}

	if (lock && sync)
		return 2;
	else if (lock)
		return 1;

	return 0;
}