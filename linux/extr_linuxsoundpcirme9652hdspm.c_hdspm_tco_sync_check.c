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
struct hdspm {int io_type; scalar_t__ tco; } ;

/* Variables and functions */
#define  AES32 131 
#define  AIO 130 
 int /*<<< orphan*/  HDSPM_RD_STATUS_1 ; 
 int /*<<< orphan*/  HDSPM_statusRegister ; 
 int HDSPM_tcoLockAes ; 
 int HDSPM_tcoLockMadi ; 
 int HDSPM_tcoSync ; 
#define  MADI 129 
#define  RayDAT 128 
 int hdspm_read (struct hdspm*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hdspm_tco_sync_check(struct hdspm *hdspm)
{
	int status;

	if (hdspm->tco) {
		switch (hdspm->io_type) {
		case MADI:
			status = hdspm_read(hdspm, HDSPM_statusRegister);
			if (status & HDSPM_tcoLockMadi) {
				if (status & HDSPM_tcoSync)
					return 2;
				else
					return 1;
			}
			return 0;
		case AES32:
			status = hdspm_read(hdspm, HDSPM_statusRegister);
			if (status & HDSPM_tcoLockAes) {
				if (status & HDSPM_tcoSync)
					return 2;
				else
					return 1;
			}
			return 0;
		case RayDAT:
		case AIO:
			status = hdspm_read(hdspm, HDSPM_RD_STATUS_1);

			if (status & 0x8000000)
				return 2; /* Sync */
			if (status & 0x4000000)
				return 1; /* Lock */
			return 0; /* No signal */

		default:
			break;
		}
	}

	return 3; /* N/A */
}