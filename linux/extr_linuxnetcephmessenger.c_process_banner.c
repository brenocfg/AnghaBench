#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ nonce; int /*<<< orphan*/  in_addr; } ;
struct TYPE_9__ {scalar_t__ nonce; int /*<<< orphan*/  in_addr; } ;
struct ceph_connection {char* error_msg; TYPE_5__* msgr; TYPE_4__ peer_addr_for_me; TYPE_4__ actual_peer_addr; TYPE_3__ peer_addr; } ;
struct TYPE_7__ {int /*<<< orphan*/  in_addr; } ;
struct TYPE_8__ {TYPE_1__ addr; } ;
struct TYPE_11__ {TYPE_2__ inst; } ;

/* Variables and functions */
 scalar_t__ addr_is_blank (int /*<<< orphan*/ *) ; 
 int addr_port (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  addr_set_port (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ceph_decode_addr (TYPE_4__*) ; 
 struct ceph_connection* ceph_pr_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dout (char*,struct ceph_connection*) ; 
 int /*<<< orphan*/  encode_my_addr (TYPE_5__*) ; 
 scalar_t__ le32_to_cpu (scalar_t__) ; 
 scalar_t__ memcmp (TYPE_3__*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_warn (char*,struct ceph_connection*,int,struct ceph_connection*,int) ; 
 scalar_t__ verify_hello (struct ceph_connection*) ; 

__attribute__((used)) static int process_banner(struct ceph_connection *con)
{
	dout("process_banner on %p\n", con);

	if (verify_hello(con) < 0)
		return -1;

	ceph_decode_addr(&con->actual_peer_addr);
	ceph_decode_addr(&con->peer_addr_for_me);

	/*
	 * Make sure the other end is who we wanted.  note that the other
	 * end may not yet know their ip address, so if it's 0.0.0.0, give
	 * them the benefit of the doubt.
	 */
	if (memcmp(&con->peer_addr, &con->actual_peer_addr,
		   sizeof(con->peer_addr)) != 0 &&
	    !(addr_is_blank(&con->actual_peer_addr.in_addr) &&
	      con->actual_peer_addr.nonce == con->peer_addr.nonce)) {
		pr_warn("wrong peer, want %s/%d, got %s/%d\n",
			ceph_pr_addr(&con->peer_addr.in_addr),
			(int)le32_to_cpu(con->peer_addr.nonce),
			ceph_pr_addr(&con->actual_peer_addr.in_addr),
			(int)le32_to_cpu(con->actual_peer_addr.nonce));
		con->error_msg = "wrong peer at address";
		return -1;
	}

	/*
	 * did we learn our address?
	 */
	if (addr_is_blank(&con->msgr->inst.addr.in_addr)) {
		int port = addr_port(&con->msgr->inst.addr.in_addr);

		memcpy(&con->msgr->inst.addr.in_addr,
		       &con->peer_addr_for_me.in_addr,
		       sizeof(con->peer_addr_for_me.in_addr));
		addr_set_port(&con->msgr->inst.addr.in_addr, port);
		encode_my_addr(con->msgr);
		dout("process_banner learned my addr is %s\n",
		     ceph_pr_addr(&con->msgr->inst.addr.in_addr));
	}

	return 0;
}