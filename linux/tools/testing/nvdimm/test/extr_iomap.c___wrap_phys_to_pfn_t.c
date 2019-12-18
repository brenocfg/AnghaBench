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
struct nfit_test_resource {int dummy; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;
typedef  int /*<<< orphan*/  pfn_t ;

/* Variables and functions */
 unsigned long PFN_MAP ; 
 struct nfit_test_resource* get_nfit_res (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phys_to_pfn_t (int /*<<< orphan*/ ,unsigned long) ; 

pfn_t __wrap_phys_to_pfn_t(phys_addr_t addr, unsigned long flags)
{
	struct nfit_test_resource *nfit_res = get_nfit_res(addr);

	if (nfit_res)
		flags &= ~PFN_MAP;
        return phys_to_pfn_t(addr, flags);
}