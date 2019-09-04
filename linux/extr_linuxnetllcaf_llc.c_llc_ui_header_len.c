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
typedef  int /*<<< orphan*/  u8 ;
struct sockaddr_llc {scalar_t__ sllc_xid; scalar_t__ sllc_test; } ;
struct sock {scalar_t__ sk_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  LLC_PDU_LEN_I ; 
 int /*<<< orphan*/  LLC_PDU_LEN_U ; 
 scalar_t__ SOCK_STREAM ; 

__attribute__((used)) static inline u8 llc_ui_header_len(struct sock *sk, struct sockaddr_llc *addr)
{
	u8 rc = LLC_PDU_LEN_U;

	if (addr->sllc_test || addr->sllc_xid)
		rc = LLC_PDU_LEN_U;
	else if (sk->sk_type == SOCK_STREAM)
		rc = LLC_PDU_LEN_I;
	return rc;
}