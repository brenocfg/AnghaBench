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
typedef  int __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_ERROR ; 
 int /*<<< orphan*/  DbgBreak () ; 
#define  RFSD_KEY_TYPE_v1_DIRECT 131 
#define  RFSD_KEY_TYPE_v1_DIRENTRY 130 
#define  RFSD_KEY_TYPE_v1_INDIRECT 129 
#define  RFSD_KEY_TYPE_v1_STAT_DATA 128 
 int RFSD_KEY_TYPE_v2_DIRECT ; 
 int RFSD_KEY_TYPE_v2_DIRENTRY ; 
 int RFSD_KEY_TYPE_v2_INDIRECT ; 
 int RFSD_KEY_TYPE_v2_STAT_DATA ; 
 int /*<<< orphan*/  RfsdPrint (int /*<<< orphan*/ ) ; 

__u32
ConvertKeyTypeUniqueness(__u32 k_uniqueness)
{
	switch (k_uniqueness)
	{
	case RFSD_KEY_TYPE_v1_STAT_DATA:		return RFSD_KEY_TYPE_v2_STAT_DATA;
	case RFSD_KEY_TYPE_v1_INDIRECT:			return RFSD_KEY_TYPE_v2_INDIRECT;
	case RFSD_KEY_TYPE_v1_DIRECT:			return RFSD_KEY_TYPE_v2_DIRECT;
	case RFSD_KEY_TYPE_v1_DIRENTRY:			return RFSD_KEY_TYPE_v2_DIRENTRY;
	
	default:
		RfsdPrint((DBG_ERROR, "Unexpected uniqueness value %i", k_uniqueness));
		// NOTE: If above value is 555, it's the 'any' value, which I'd be surprised to see on disk.
		DbgBreak();
		return 0xF;	// We'll return v2 'any', just to see what happens...
	}
}