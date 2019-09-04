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
struct dccp_ackvec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dccp_ackvec_purge_records (struct dccp_ackvec*) ; 
 int /*<<< orphan*/  dccp_ackvec_slab ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct dccp_ackvec*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 

void dccp_ackvec_free(struct dccp_ackvec *av)
{
	if (likely(av != NULL)) {
		dccp_ackvec_purge_records(av);
		kmem_cache_free(dccp_ackvec_slab, av);
	}
}