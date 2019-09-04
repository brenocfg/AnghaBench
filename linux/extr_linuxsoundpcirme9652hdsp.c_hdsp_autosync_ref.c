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
struct hdsp {int dummy; } ;

/* Variables and functions */
 int HDSP_AUTOSYNC_FROM_ADAT1 ; 
 int HDSP_AUTOSYNC_FROM_ADAT2 ; 
 int HDSP_AUTOSYNC_FROM_ADAT3 ; 
 int HDSP_AUTOSYNC_FROM_ADAT_SYNC ; 
 int HDSP_AUTOSYNC_FROM_NONE ; 
 int HDSP_AUTOSYNC_FROM_SPDIF ; 
 int HDSP_AUTOSYNC_FROM_WORD ; 
#define  HDSP_SelSyncRefMask 134 
#define  HDSP_SelSyncRef_ADAT1 133 
#define  HDSP_SelSyncRef_ADAT2 132 
#define  HDSP_SelSyncRef_ADAT3 131 
#define  HDSP_SelSyncRef_ADAT_SYNC 130 
#define  HDSP_SelSyncRef_SPDIF 129 
#define  HDSP_SelSyncRef_WORD 128 
 int /*<<< orphan*/  HDSP_status2Register ; 
 unsigned int hdsp_read (struct hdsp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hdsp_autosync_ref(struct hdsp *hdsp)
{
	/* This looks at the autosync selected sync reference */
	unsigned int status2 = hdsp_read(hdsp, HDSP_status2Register);

	switch (status2 & HDSP_SelSyncRefMask) {
	case HDSP_SelSyncRef_WORD:
		return HDSP_AUTOSYNC_FROM_WORD;
	case HDSP_SelSyncRef_ADAT_SYNC:
		return HDSP_AUTOSYNC_FROM_ADAT_SYNC;
	case HDSP_SelSyncRef_SPDIF:
		return HDSP_AUTOSYNC_FROM_SPDIF;
	case HDSP_SelSyncRefMask:
		return HDSP_AUTOSYNC_FROM_NONE;
	case HDSP_SelSyncRef_ADAT1:
		return HDSP_AUTOSYNC_FROM_ADAT1;
	case HDSP_SelSyncRef_ADAT2:
		return HDSP_AUTOSYNC_FROM_ADAT2;
	case HDSP_SelSyncRef_ADAT3:
		return HDSP_AUTOSYNC_FROM_ADAT3;
	default:
		return HDSP_AUTOSYNC_FROM_WORD;
	}
	return 0;
}