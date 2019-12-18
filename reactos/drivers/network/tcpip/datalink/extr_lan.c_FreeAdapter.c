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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  PLAN_ADAPTER ;

/* Variables and functions */
 int /*<<< orphan*/  ExFreePoolWithTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LAN_ADAPTER_TAG ; 

VOID FreeAdapter(
    PLAN_ADAPTER Adapter)
/*
 * FUNCTION: Frees memory for a LAN_ADAPTER structure
 * ARGUMENTS:
 *     Adapter = Pointer to LAN_ADAPTER structure to free
 */
{
    ExFreePoolWithTag(Adapter, LAN_ADAPTER_TAG);
}