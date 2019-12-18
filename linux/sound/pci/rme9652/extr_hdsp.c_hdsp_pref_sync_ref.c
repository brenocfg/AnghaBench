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
struct hdsp {int control_register; } ;

/* Variables and functions */
 int HDSP_SYNC_FROM_ADAT1 ; 
 int HDSP_SYNC_FROM_ADAT2 ; 
 int HDSP_SYNC_FROM_ADAT3 ; 
 int HDSP_SYNC_FROM_ADAT_SYNC ; 
 int HDSP_SYNC_FROM_SPDIF ; 
 int HDSP_SYNC_FROM_WORD ; 
 int HDSP_SyncRefMask ; 
#define  HDSP_SyncRef_ADAT1 133 
#define  HDSP_SyncRef_ADAT2 132 
#define  HDSP_SyncRef_ADAT3 131 
#define  HDSP_SyncRef_ADAT_SYNC 130 
#define  HDSP_SyncRef_SPDIF 129 
#define  HDSP_SyncRef_WORD 128 

__attribute__((used)) static int hdsp_pref_sync_ref(struct hdsp *hdsp)
{
	/* Notice that this looks at the requested sync source,
	   not the one actually in use.
	*/

	switch (hdsp->control_register & HDSP_SyncRefMask) {
	case HDSP_SyncRef_ADAT1:
		return HDSP_SYNC_FROM_ADAT1;
	case HDSP_SyncRef_ADAT2:
		return HDSP_SYNC_FROM_ADAT2;
	case HDSP_SyncRef_ADAT3:
		return HDSP_SYNC_FROM_ADAT3;
	case HDSP_SyncRef_SPDIF:
		return HDSP_SYNC_FROM_SPDIF;
	case HDSP_SyncRef_WORD:
		return HDSP_SYNC_FROM_WORD;
	case HDSP_SyncRef_ADAT_SYNC:
		return HDSP_SYNC_FROM_ADAT_SYNC;
	default:
		return HDSP_SYNC_FROM_WORD;
	}
	return 0;
}