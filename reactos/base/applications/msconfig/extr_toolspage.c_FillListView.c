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
 int /*<<< orphan*/  AddItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSIDL_SYSTEM ; 
 int /*<<< orphan*/  CSIDL_WINDOWS ; 
 int /*<<< orphan*/  IDS_TOOLS_CMD_CMD ; 
 int /*<<< orphan*/  IDS_TOOLS_CMD_DESCR ; 
 int /*<<< orphan*/  IDS_TOOLS_CMD_NAME ; 
 int /*<<< orphan*/  IDS_TOOLS_CMD_PARAM ; 
 int /*<<< orphan*/  IDS_TOOLS_INFO_CMD ; 
 int /*<<< orphan*/  IDS_TOOLS_INFO_DESCR ; 
 int /*<<< orphan*/  IDS_TOOLS_INFO_NAME ; 
 int /*<<< orphan*/  IDS_TOOLS_INFO_PARAM ; 
 int /*<<< orphan*/  IDS_TOOLS_REGEDIT_CMD ; 
 int /*<<< orphan*/  IDS_TOOLS_REGEDIT_DESCR ; 
 int /*<<< orphan*/  IDS_TOOLS_REGEDIT_NAME ; 
 int /*<<< orphan*/  IDS_TOOLS_REGEDIT_PARAM ; 
 int /*<<< orphan*/  IDS_TOOLS_SYSDM_CMD ; 
 int /*<<< orphan*/  IDS_TOOLS_SYSDM_DESCR ; 
 int /*<<< orphan*/  IDS_TOOLS_SYSDM_NAME ; 
 int /*<<< orphan*/  IDS_TOOLS_SYSDM_PARAM ; 

void FillListView ( void ) {
    AddItem(IDS_TOOLS_CMD_NAME, IDS_TOOLS_CMD_DESCR, IDS_TOOLS_CMD_CMD, IDS_TOOLS_CMD_PARAM, CSIDL_SYSTEM);
    AddItem(IDS_TOOLS_REGEDIT_NAME, IDS_TOOLS_REGEDIT_DESCR, IDS_TOOLS_REGEDIT_CMD,IDS_TOOLS_REGEDIT_PARAM, CSIDL_WINDOWS);
    AddItem(IDS_TOOLS_SYSDM_NAME, IDS_TOOLS_SYSDM_DESCR, IDS_TOOLS_SYSDM_CMD, IDS_TOOLS_SYSDM_PARAM, CSIDL_SYSTEM);
    AddItem(IDS_TOOLS_INFO_NAME, IDS_TOOLS_INFO_DESCR, IDS_TOOLS_INFO_CMD, IDS_TOOLS_INFO_PARAM, CSIDL_SYSTEM);
}