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
struct symt_ht {int /*<<< orphan*/  symt; } ;
struct module {int num_sorttab; struct symt_ht** addr_sorttab; int /*<<< orphan*/  sortlist_valid; } ;
typedef  scalar_t__ ULONG64 ;
typedef  scalar_t__ DWORD_PTR ;

/* Variables and functions */
 scalar_t__ cmp_sorttab_addr (struct module*,int,scalar_t__) ; 
 int /*<<< orphan*/  resort_symbols (struct module*) ; 
 int /*<<< orphan*/  symt_get_address (int /*<<< orphan*/ *,scalar_t__*) ; 
 int symt_get_best_at (struct module*,int) ; 
 int /*<<< orphan*/  symt_get_length (struct module*,int /*<<< orphan*/ *,scalar_t__*) ; 

struct symt_ht* symt_find_nearest(struct module* module, DWORD_PTR addr)
{
    int         mid, high, low;
    ULONG64     ref_addr, ref_size;

    if (!module->sortlist_valid || !module->addr_sorttab)
    {
        if (!resort_symbols(module)) return NULL;
    }

    /*
     * Binary search to find closest symbol.
     */
    low = 0;
    high = module->num_sorttab;

    symt_get_address(&module->addr_sorttab[0]->symt, &ref_addr);
    if (addr <= ref_addr)
    {
        low = symt_get_best_at(module, 0);
        return module->addr_sorttab[low];
    }

    if (high)
    {
        symt_get_address(&module->addr_sorttab[high - 1]->symt, &ref_addr);
        symt_get_length(module, &module->addr_sorttab[high - 1]->symt, &ref_size);
        if (addr >= ref_addr + ref_size) return NULL;
    }
    
    while (high > low + 1)
    {
        mid = (high + low) / 2;
        if (cmp_sorttab_addr(module, mid, addr) < 0)
            low = mid;
        else
            high = mid;
    }
    if (low != high && high != module->num_sorttab &&
        cmp_sorttab_addr(module, high, addr) <= 0)
        low = high;

    /* If found symbol is a public symbol, check if there are any other entries that
     * might also have the same address, but would get better information
     */
    low = symt_get_best_at(module, low);

    /* finally check that we fit into the found symbol */
    //symt_get_address(&module->addr_sorttab[low]->symt, &ref_addr);
    //if (addr < ref_addr) return NULL;
    //symt_get_length(module, &module->addr_sorttab[low]->symt, &ref_size);
    //if (addr >= ref_addr + ref_size) return NULL;

    return module->addr_sorttab[low];
}