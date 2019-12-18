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
struct hdspm {scalar_t__ io_type; } ;

/* Variables and functions */
 scalar_t__ AES32 ; 
 int HDSPM_AES32_AUTOSYNC_FROM_NONE ; 
 unsigned int HDSPM_AES32_AUTOSYNC_FROM_SYNC_IN ; 
 unsigned int HDSPM_AES32_AUTOSYNC_FROM_WORD ; 
 unsigned int HDSPM_AES32_syncref_bit ; 
 int HDSPM_AUTOSYNC_FROM_MADI ; 
 int HDSPM_AUTOSYNC_FROM_NONE ; 
 int HDSPM_AUTOSYNC_FROM_SYNC_IN ; 
 int HDSPM_AUTOSYNC_FROM_TCO ; 
 int HDSPM_AUTOSYNC_FROM_WORD ; 
 unsigned int HDSPM_SelSyncRefMask ; 
#define  HDSPM_SelSyncRef_MADI 132 
#define  HDSPM_SelSyncRef_NVALID 131 
#define  HDSPM_SelSyncRef_SyncIn 130 
#define  HDSPM_SelSyncRef_TCO 129 
#define  HDSPM_SelSyncRef_WORD 128 
 int /*<<< orphan*/  HDSPM_statusRegister ; 
 int /*<<< orphan*/  HDSPM_statusRegister2 ; 
 scalar_t__ MADI ; 
 unsigned int hdspm_read (struct hdspm*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hdspm_autosync_ref(struct hdspm *hdspm)
{
	/* This looks at the autosync selected sync reference */
	if (AES32 == hdspm->io_type) {

		unsigned int status = hdspm_read(hdspm, HDSPM_statusRegister);
		unsigned int syncref = (status >> HDSPM_AES32_syncref_bit) & 0xF;
		if ((syncref >= HDSPM_AES32_AUTOSYNC_FROM_WORD) &&
				(syncref <= HDSPM_AES32_AUTOSYNC_FROM_SYNC_IN)) {
			return syncref;
		}
		return HDSPM_AES32_AUTOSYNC_FROM_NONE;

	} else if (MADI == hdspm->io_type) {

		unsigned int status2 = hdspm_read(hdspm, HDSPM_statusRegister2);
		switch (status2 & HDSPM_SelSyncRefMask) {
		case HDSPM_SelSyncRef_WORD:
			return HDSPM_AUTOSYNC_FROM_WORD;
		case HDSPM_SelSyncRef_MADI:
			return HDSPM_AUTOSYNC_FROM_MADI;
		case HDSPM_SelSyncRef_TCO:
			return HDSPM_AUTOSYNC_FROM_TCO;
		case HDSPM_SelSyncRef_SyncIn:
			return HDSPM_AUTOSYNC_FROM_SYNC_IN;
		case HDSPM_SelSyncRef_NVALID:
			return HDSPM_AUTOSYNC_FROM_NONE;
		default:
			return HDSPM_AUTOSYNC_FROM_NONE;
		}

	}
	return 0;
}