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
struct wined3d_adapter {scalar_t__ vram_bytes_used; } ;
typedef  scalar_t__ UINT64 ;
typedef  scalar_t__ INT64 ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wine_dbgstr_longlong (scalar_t__) ; 

UINT64 adapter_adjust_memory(struct wined3d_adapter *adapter, INT64 amount)
{
    adapter->vram_bytes_used += amount;
    TRACE("Adjusted used adapter memory by 0x%s to 0x%s.\n",
            wine_dbgstr_longlong(amount),
            wine_dbgstr_longlong(adapter->vram_bytes_used));
    return adapter->vram_bytes_used;
}