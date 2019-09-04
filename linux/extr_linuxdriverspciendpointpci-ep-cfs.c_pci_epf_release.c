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
struct pci_epf_group {int /*<<< orphan*/  epf; int /*<<< orphan*/  index; } ;
struct config_item {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  functions_idr ; 
 int /*<<< orphan*/  functions_mutex ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct pci_epf_group*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_epf_destroy (int /*<<< orphan*/ ) ; 
 struct pci_epf_group* to_pci_epf_group (struct config_item*) ; 

__attribute__((used)) static void pci_epf_release(struct config_item *item)
{
	struct pci_epf_group *epf_group = to_pci_epf_group(item);

	mutex_lock(&functions_mutex);
	idr_remove(&functions_idr, epf_group->index);
	mutex_unlock(&functions_mutex);
	pci_epf_destroy(epf_group->epf);
	kfree(epf_group);
}