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
typedef  int /*<<< orphan*/  SLIST_HEADER ;
typedef  scalar_t__ PSLIST_HEADER ;
typedef  int /*<<< orphan*/  HINSTANCE ;

/* Variables and functions */
 int /*<<< orphan*/  HeapCreate (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlInitializeSListHead (scalar_t__) ; 
 scalar_t__ ShimLib_ShimMalloc (int) ; 
 int /*<<< orphan*/  g_ShimLib_Heap ; 
 int /*<<< orphan*/  g_ShimLib_hInstance ; 
 scalar_t__ g_UsedShims ; 

void ShimLib_Init(HINSTANCE hInstance)
{
    g_ShimLib_hInstance = hInstance;
    g_ShimLib_Heap = HeapCreate(0, 0x10000, 0);

    g_UsedShims = (PSLIST_HEADER)ShimLib_ShimMalloc(sizeof(SLIST_HEADER));
    RtlInitializeSListHead(g_UsedShims);
}