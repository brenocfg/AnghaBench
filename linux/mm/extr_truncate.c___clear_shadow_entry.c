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
struct address_space {int /*<<< orphan*/  nrexceptional; int /*<<< orphan*/  i_pages; } ;
typedef  int /*<<< orphan*/  pgoff_t ;

/* Variables and functions */
 int /*<<< orphan*/  XA_STATE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  workingset_update_node ; 
 int /*<<< orphan*/  xas ; 
 void* xas_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xas_set_update (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xas_store (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void __clear_shadow_entry(struct address_space *mapping,
				pgoff_t index, void *entry)
{
	XA_STATE(xas, &mapping->i_pages, index);

	xas_set_update(&xas, workingset_update_node);
	if (xas_load(&xas) != entry)
		return;
	xas_store(&xas, NULL);
	mapping->nrexceptional--;
}