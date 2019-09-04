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
struct islpci_acl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  prism54_clear_mac (struct islpci_acl*) ; 

void
prism54_acl_clean(struct islpci_acl *acl)
{
	prism54_clear_mac(acl);
}