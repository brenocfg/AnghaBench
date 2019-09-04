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
struct nfc_llcp_local {int dummy; } ;
struct nfc_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  local_cleanup (struct nfc_llcp_local*) ; 
 struct nfc_llcp_local* nfc_llcp_find_local (struct nfc_dev*) ; 
 int /*<<< orphan*/  nfc_llcp_local_put (struct nfc_llcp_local*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

void nfc_llcp_unregister_device(struct nfc_dev *dev)
{
	struct nfc_llcp_local *local = nfc_llcp_find_local(dev);

	if (local == NULL) {
		pr_debug("No such device\n");
		return;
	}

	local_cleanup(local);

	nfc_llcp_local_put(local);
}