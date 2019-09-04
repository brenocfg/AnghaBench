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

/* Variables and functions */
 struct nfit_test_resource* get_nfit_res (long) ; 
 void memunmap (void*) ; 

void __wrap_memunmap(void *addr)
{
	struct nfit_test_resource *nfit_res = get_nfit_res((long) addr);

	if (nfit_res)
		return;
	return memunmap(addr);
}