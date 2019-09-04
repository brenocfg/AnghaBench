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
struct nfc_llcp_sock {scalar_t__ remote_miu; int /*<<< orphan*/  remote_rw; } ;

/* Variables and functions */
 int /*<<< orphan*/  LLCP_DEFAULT_RW ; 
 scalar_t__ LLCP_MAX_MIU ; 

void nfc_llcp_socket_remote_param_init(struct nfc_llcp_sock *sock)
{
	sock->remote_rw = LLCP_DEFAULT_RW;
	sock->remote_miu = LLCP_MAX_MIU + 1;
}