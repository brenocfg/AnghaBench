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
struct hdsp {int /*<<< orphan*/  control_register; } ;

/* Variables and functions */
#define  HDSP_SYNC_FROM_ADAT1 133 
#define  HDSP_SYNC_FROM_ADAT2 132 
#define  HDSP_SYNC_FROM_ADAT3 131 
#define  HDSP_SYNC_FROM_ADAT_SYNC 130 
#define  HDSP_SYNC_FROM_SPDIF 129 
#define  HDSP_SYNC_FROM_WORD 128 
 int /*<<< orphan*/  HDSP_SyncRefMask ; 
 int /*<<< orphan*/  HDSP_SyncRef_ADAT2 ; 
 int /*<<< orphan*/  HDSP_SyncRef_ADAT3 ; 
 int /*<<< orphan*/  HDSP_SyncRef_ADAT_SYNC ; 
 int /*<<< orphan*/  HDSP_SyncRef_SPDIF ; 
 int /*<<< orphan*/  HDSP_SyncRef_WORD ; 
 int /*<<< orphan*/  HDSP_controlRegister ; 
 int /*<<< orphan*/  hdsp_write (struct hdsp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hdsp_set_pref_sync_ref(struct hdsp *hdsp, int pref)
{
	hdsp->control_register &= ~HDSP_SyncRefMask;
	switch (pref) {
	case HDSP_SYNC_FROM_ADAT1:
		hdsp->control_register &= ~HDSP_SyncRefMask; /* clear SyncRef bits */
		break;
	case HDSP_SYNC_FROM_ADAT2:
		hdsp->control_register |= HDSP_SyncRef_ADAT2;
		break;
	case HDSP_SYNC_FROM_ADAT3:
		hdsp->control_register |= HDSP_SyncRef_ADAT3;
		break;
	case HDSP_SYNC_FROM_SPDIF:
		hdsp->control_register |= HDSP_SyncRef_SPDIF;
		break;
	case HDSP_SYNC_FROM_WORD:
		hdsp->control_register |= HDSP_SyncRef_WORD;
		break;
	case HDSP_SYNC_FROM_ADAT_SYNC:
		hdsp->control_register |= HDSP_SyncRef_ADAT_SYNC;
		break;
	default:
		return -1;
	}
	hdsp_write(hdsp, HDSP_controlRegister, hdsp->control_register);
	return 0;
}