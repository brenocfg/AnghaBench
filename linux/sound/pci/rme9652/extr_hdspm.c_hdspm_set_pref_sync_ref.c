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
struct hdspm {int io_type; int control_register; int settings_register; int /*<<< orphan*/  tco; } ;

/* Variables and functions */
#define  AES32 132 
#define  AIO 131 
 int HDSPM_SyncRef0 ; 
 int HDSPM_SyncRef1 ; 
 int HDSPM_SyncRef2 ; 
 int HDSPM_SyncRef3 ; 
 int HDSPM_SyncRefMask ; 
 int /*<<< orphan*/  HDSPM_WR_SETTINGS ; 
 int HDSPM_c0_SyncRef0 ; 
 int HDSPM_c0_SyncRefMask ; 
 int /*<<< orphan*/  HDSPM_controlRegister ; 
#define  MADI 130 
#define  MADIface 129 
#define  RayDAT 128 
 int /*<<< orphan*/  hdspm_write (struct hdspm*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hdspm_set_pref_sync_ref(struct hdspm * hdspm, int pref)
{
	int p = 0;

	switch (hdspm->io_type) {
	case AES32:
		hdspm->control_register &= ~HDSPM_SyncRefMask;
		switch (pref) {
		case 0: /* WC  */
			break;
		case 1: /* AES 1 */
			hdspm->control_register |= HDSPM_SyncRef0;
			break;
		case 2: /* AES 2 */
			hdspm->control_register |= HDSPM_SyncRef1;
			break;
		case 3: /* AES 3 */
			hdspm->control_register |=
				HDSPM_SyncRef1+HDSPM_SyncRef0;
			break;
		case 4: /* AES 4 */
			hdspm->control_register |= HDSPM_SyncRef2;
			break;
		case 5: /* AES 5 */
			hdspm->control_register |=
				HDSPM_SyncRef2+HDSPM_SyncRef0;
			break;
		case 6: /* AES 6 */
			hdspm->control_register |=
				HDSPM_SyncRef2+HDSPM_SyncRef1;
			break;
		case 7: /* AES 7 */
			hdspm->control_register |=
				HDSPM_SyncRef2+HDSPM_SyncRef1+HDSPM_SyncRef0;
			break;
		case 8: /* AES 8 */
			hdspm->control_register |= HDSPM_SyncRef3;
			break;
		case 9: /* TCO */
			hdspm->control_register |=
				HDSPM_SyncRef3+HDSPM_SyncRef0;
			break;
		default:
			return -1;
		}

		break;

	case MADI:
	case MADIface:
		hdspm->control_register &= ~HDSPM_SyncRefMask;
		if (hdspm->tco) {
			switch (pref) {
			case 0: /* WC */
				break;
			case 1: /* MADI */
				hdspm->control_register |= HDSPM_SyncRef0;
				break;
			case 2: /* TCO */
				hdspm->control_register |= HDSPM_SyncRef1;
				break;
			case 3: /* SYNC_IN */
				hdspm->control_register |=
					HDSPM_SyncRef0+HDSPM_SyncRef1;
				break;
			default:
				return -1;
			}
		} else {
			switch (pref) {
			case 0: /* WC */
				break;
			case 1: /* MADI */
				hdspm->control_register |= HDSPM_SyncRef0;
				break;
			case 2: /* SYNC_IN */
				hdspm->control_register |=
					HDSPM_SyncRef0+HDSPM_SyncRef1;
				break;
			default:
				return -1;
			}
		}

		break;

	case RayDAT:
		if (hdspm->tco) {
			switch (pref) {
			case 0: p = 0; break;  /* WC */
			case 1: p = 3; break;  /* ADAT 1 */
			case 2: p = 4; break;  /* ADAT 2 */
			case 3: p = 5; break;  /* ADAT 3 */
			case 4: p = 6; break;  /* ADAT 4 */
			case 5: p = 1; break;  /* AES */
			case 6: p = 2; break;  /* SPDIF */
			case 7: p = 9; break;  /* TCO */
			case 8: p = 10; break; /* SYNC_IN */
			default: return -1;
			}
		} else {
			switch (pref) {
			case 0: p = 0; break;  /* WC */
			case 1: p = 3; break;  /* ADAT 1 */
			case 2: p = 4; break;  /* ADAT 2 */
			case 3: p = 5; break;  /* ADAT 3 */
			case 4: p = 6; break;  /* ADAT 4 */
			case 5: p = 1; break;  /* AES */
			case 6: p = 2; break;  /* SPDIF */
			case 7: p = 10; break; /* SYNC_IN */
			default: return -1;
			}
		}
		break;

	case AIO:
		if (hdspm->tco) {
			switch (pref) {
			case 0: p = 0; break;  /* WC */
			case 1: p = 3; break;  /* ADAT */
			case 2: p = 1; break;  /* AES */
			case 3: p = 2; break;  /* SPDIF */
			case 4: p = 9; break;  /* TCO */
			case 5: p = 10; break; /* SYNC_IN */
			default: return -1;
			}
		} else {
			switch (pref) {
			case 0: p = 0; break;  /* WC */
			case 1: p = 3; break;  /* ADAT */
			case 2: p = 1; break;  /* AES */
			case 3: p = 2; break;  /* SPDIF */
			case 4: p = 10; break; /* SYNC_IN */
			default: return -1;
			}
		}
		break;
	}

	switch (hdspm->io_type) {
	case RayDAT:
	case AIO:
		hdspm->settings_register &= ~HDSPM_c0_SyncRefMask;
		hdspm->settings_register |= HDSPM_c0_SyncRef0 * p;
		hdspm_write(hdspm, HDSPM_WR_SETTINGS, hdspm->settings_register);
		break;

	case MADI:
	case MADIface:
	case AES32:
		hdspm_write(hdspm, HDSPM_controlRegister,
				hdspm->control_register);
	}

	return 0;
}