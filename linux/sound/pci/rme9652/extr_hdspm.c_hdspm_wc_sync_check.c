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
 int HDSPM_AES32_wcLock ; 
 int HDSPM_AES32_wcSync ; 
 int /*<<< orphan*/  HDSPM_statusRegister ; 
 int /*<<< orphan*/  HDSPM_statusRegister2 ; 
 int HDSPM_wcLock ; 
 int HDSPM_wcSync ; 
#define  MADI 130 
#define  MADIface 129 
#define  RayDAT 128 
 int hdspm_read (struct hdspm*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hdspm_wc_sync_check(struct hdspm *hdspm)
{
	int status, status2;

	switch (hdspm->io_type) {
	case AES32:
		status = hdspm_read(hdspm, HDSPM_statusRegister);
		if (status & HDSPM_AES32_wcLock) {
			if (status & HDSPM_AES32_wcSync)
				return 2;
			else
				return 1;
		}
		return 0;
		break;

	case MADI:
		status2 = hdspm_read(hdspm, HDSPM_statusRegister2);
		if (status2 & HDSPM_wcLock) {
			if (status2 & HDSPM_wcSync)
				return 2;
			else
				return 1;
		}
		return 0;
		break;

	case RayDAT:
	case AIO:
		status = hdspm_read(hdspm, HDSPM_statusRegister);

		if (status & 0x2000000)
			return 2;
		else if (status & 0x1000000)
			return 1;
		return 0;

		break;

	case MADIface:
		break;
	}


	return 3;
}