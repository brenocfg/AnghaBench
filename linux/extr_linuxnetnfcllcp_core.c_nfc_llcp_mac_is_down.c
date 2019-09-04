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
struct nfc_llcp_local {int /*<<< orphan*/  remote_lto; int /*<<< orphan*/  remote_miu; } ;
struct nfc_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LLCP_DEFAULT_LTO ; 
 int /*<<< orphan*/  LLCP_DEFAULT_MIU ; 
 struct nfc_llcp_local* nfc_llcp_find_local (struct nfc_dev*) ; 
 int /*<<< orphan*/  nfc_llcp_socket_release (struct nfc_llcp_local*,int,int /*<<< orphan*/ ) ; 

void nfc_llcp_mac_is_down(struct nfc_dev *dev)
{
	struct nfc_llcp_local *local;

	local = nfc_llcp_find_local(dev);
	if (local == NULL)
		return;

	local->remote_miu = LLCP_DEFAULT_MIU;
	local->remote_lto = LLCP_DEFAULT_LTO;

	/* Close and purge all existing sockets */
	nfc_llcp_socket_release(local, true, 0);
}