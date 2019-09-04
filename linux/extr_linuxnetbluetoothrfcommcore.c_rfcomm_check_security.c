#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct rfcomm_dlc {int /*<<< orphan*/  out; int /*<<< orphan*/  sec_level; TYPE_2__* session; } ;
struct l2cap_conn {int /*<<< orphan*/  hcon; } ;
typedef  int /*<<< orphan*/  __u8 ;
struct TYPE_8__ {TYPE_3__* chan; } ;
struct TYPE_7__ {struct l2cap_conn* conn; } ;
struct TYPE_6__ {TYPE_1__* sock; } ;
struct TYPE_5__ {struct sock* sk; } ;

/* Variables and functions */
#define  BT_SECURITY_FIPS 130 
#define  BT_SECURITY_HIGH 129 
#define  BT_SECURITY_MEDIUM 128 
 int /*<<< orphan*/  HCI_AT_GENERAL_BONDING ; 
 int /*<<< orphan*/  HCI_AT_GENERAL_BONDING_MITM ; 
 int /*<<< orphan*/  HCI_AT_NO_BONDING ; 
 int hci_conn_security (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* l2cap_pi (struct sock*) ; 

__attribute__((used)) static int rfcomm_check_security(struct rfcomm_dlc *d)
{
	struct sock *sk = d->session->sock->sk;
	struct l2cap_conn *conn = l2cap_pi(sk)->chan->conn;

	__u8 auth_type;

	switch (d->sec_level) {
	case BT_SECURITY_HIGH:
	case BT_SECURITY_FIPS:
		auth_type = HCI_AT_GENERAL_BONDING_MITM;
		break;
	case BT_SECURITY_MEDIUM:
		auth_type = HCI_AT_GENERAL_BONDING;
		break;
	default:
		auth_type = HCI_AT_NO_BONDING;
		break;
	}

	return hci_conn_security(conn->hcon, d->sec_level, auth_type,
				 d->out);
}