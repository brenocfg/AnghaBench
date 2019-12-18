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
struct module {int dummy; } ;
typedef  int /*<<< orphan*/  ULONG64 ;

/* Variables and functions */
 int cmp_sorttab_addr (struct module*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  symt_get_address (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline unsigned where_to_insert(struct module* module, unsigned high, const struct symt_ht* elt)
{
    unsigned    low = 0, mid = high / 2;
    ULONG64     addr;

    if (!high) return 0;
    symt_get_address(&elt->symt, &addr);
    do
    {
        switch (cmp_sorttab_addr(module, mid, addr))
        {
        case 0: return mid;
        case -1: low = mid + 1; break;
        case 1: high = mid; break;
        }
        mid = low + (high - low) / 2;
    } while (low < high);
    return mid;
}