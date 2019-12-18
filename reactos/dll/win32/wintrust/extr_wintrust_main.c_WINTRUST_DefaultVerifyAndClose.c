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
typedef  int /*<<< orphan*/  WINTRUST_DATA ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  GUID ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  WINTRUST_DefaultClose (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WINTRUST_DefaultVerify (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static LONG WINTRUST_DefaultVerifyAndClose(HWND hwnd, GUID *actionID,
 WINTRUST_DATA *data)
{
    LONG err;

    TRACE("(%p, %s, %p)\n", hwnd, debugstr_guid(actionID), data);

    err = WINTRUST_DefaultVerify(hwnd, actionID, data);
    WINTRUST_DefaultClose(hwnd, actionID, data);
    TRACE("returning %08x\n", err);
    return err;
}