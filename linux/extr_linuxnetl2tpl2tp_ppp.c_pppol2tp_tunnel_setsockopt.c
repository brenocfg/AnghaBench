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
struct sock {int dummy; } ;
struct l2tp_tunnel {int debug; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOPROTOOPT ; 
 int /*<<< orphan*/  L2TP_MSG_CONTROL ; 
#define  PPPOL2TP_SO_DEBUG 128 
 int /*<<< orphan*/  l2tp_info (struct l2tp_tunnel*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pppol2tp_tunnel_setsockopt(struct sock *sk,
				      struct l2tp_tunnel *tunnel,
				      int optname, int val)
{
	int err = 0;

	switch (optname) {
	case PPPOL2TP_SO_DEBUG:
		tunnel->debug = val;
		l2tp_info(tunnel, L2TP_MSG_CONTROL, "%s: set debug=%x\n",
			  tunnel->name, tunnel->debug);
		break;

	default:
		err = -ENOPROTOOPT;
		break;
	}

	return err;
}