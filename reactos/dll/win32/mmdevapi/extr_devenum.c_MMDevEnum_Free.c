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
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * MMDevEnumerator ; 
 int /*<<< orphan*/  MMDevice_Destroy (int /*<<< orphan*/ ) ; 
 scalar_t__ MMDevice_count ; 
 int /*<<< orphan*/ * MMDevice_head ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * key_capture ; 
 int /*<<< orphan*/ * key_render ; 

void MMDevEnum_Free(void)
{
    while (MMDevice_count)
        MMDevice_Destroy(MMDevice_head[0]);
    RegCloseKey(key_render);
    RegCloseKey(key_capture);
    key_render = key_capture = NULL;
    HeapFree(GetProcessHeap(), 0, MMDevEnumerator);
    MMDevEnumerator = NULL;
}