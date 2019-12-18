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
struct work_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_replace_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pending ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmci_transport_cleanup_list ; 
 int /*<<< orphan*/  vmci_transport_cleanup_lock ; 
 int /*<<< orphan*/  vmci_transport_free_resources (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vmci_transport_cleanup(struct work_struct *work)
{
	LIST_HEAD(pending);

	spin_lock_bh(&vmci_transport_cleanup_lock);
	list_replace_init(&vmci_transport_cleanup_list, &pending);
	spin_unlock_bh(&vmci_transport_cleanup_lock);
	vmci_transport_free_resources(&pending);
}