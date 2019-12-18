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
struct d3dx_regstore {int /*<<< orphan*/ * tables; } ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int PRES_REGTAB_COUNT ; 

__attribute__((used)) static void regstore_free_tables(struct d3dx_regstore *rs)
{
    unsigned int i;

    for (i = 0; i < PRES_REGTAB_COUNT; ++i)
    {
        HeapFree(GetProcessHeap(), 0, rs->tables[i]);
    }
}