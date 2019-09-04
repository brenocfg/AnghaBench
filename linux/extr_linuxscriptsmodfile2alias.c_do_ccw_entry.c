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

/* Variables and functions */
 int /*<<< orphan*/  ADD (char*,char*,int,int) ; 
 int CCW_DEVICE_ID_MATCH_CU_MODEL ; 
 int CCW_DEVICE_ID_MATCH_CU_TYPE ; 
 int CCW_DEVICE_ID_MATCH_DEVICE_MODEL ; 
 int CCW_DEVICE_ID_MATCH_DEVICE_TYPE ; 
 int /*<<< orphan*/  DEF_FIELD (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  add_wildcard (char*) ; 
 int /*<<< orphan*/  ccw_device_id ; 
 int cu_model ; 
 int cu_type ; 
 int dev_model ; 
 int dev_type ; 
 int match_flags ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static int do_ccw_entry(const char *filename,
			void *symval, char *alias)
{
	DEF_FIELD(symval, ccw_device_id, match_flags);
	DEF_FIELD(symval, ccw_device_id, cu_type);
	DEF_FIELD(symval, ccw_device_id, cu_model);
	DEF_FIELD(symval, ccw_device_id, dev_type);
	DEF_FIELD(symval, ccw_device_id, dev_model);

	strcpy(alias, "ccw:");
	ADD(alias, "t", match_flags&CCW_DEVICE_ID_MATCH_CU_TYPE,
	    cu_type);
	ADD(alias, "m", match_flags&CCW_DEVICE_ID_MATCH_CU_MODEL,
	    cu_model);
	ADD(alias, "dt", match_flags&CCW_DEVICE_ID_MATCH_DEVICE_TYPE,
	    dev_type);
	ADD(alias, "dm", match_flags&CCW_DEVICE_ID_MATCH_DEVICE_MODEL,
	    dev_model);
	add_wildcard(alias);
	return 1;
}