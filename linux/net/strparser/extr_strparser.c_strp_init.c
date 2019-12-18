#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  abort_parser; int /*<<< orphan*/  read_sock_done; scalar_t__ parse_msg; scalar_t__ rcv_msg; int /*<<< orphan*/  unlock; int /*<<< orphan*/  lock; } ;
struct strparser {int /*<<< orphan*/  work; int /*<<< orphan*/  msg_timer_work; TYPE_1__ cb; struct sock* sk; } ;
struct strp_callbacks {scalar_t__ abort_parser; scalar_t__ read_sock_done; scalar_t__ parse_msg; scalar_t__ rcv_msg; scalar_t__ unlock; scalar_t__ lock; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  default_read_sock_done ; 
 int /*<<< orphan*/  memset (struct strparser*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strp_abort_strp ; 
 int /*<<< orphan*/  strp_msg_timeout ; 
 int /*<<< orphan*/  strp_sock_lock ; 
 int /*<<< orphan*/  strp_sock_unlock ; 
 int /*<<< orphan*/  strp_work ; 

int strp_init(struct strparser *strp, struct sock *sk,
	      const struct strp_callbacks *cb)
{

	if (!cb || !cb->rcv_msg || !cb->parse_msg)
		return -EINVAL;

	/* The sk (sock) arg determines the mode of the stream parser.
	 *
	 * If the sock is set then the strparser is in receive callback mode.
	 * The upper layer calls strp_data_ready to kick receive processing
	 * and strparser calls the read_sock function on the socket to
	 * get packets.
	 *
	 * If the sock is not set then the strparser is in general mode.
	 * The upper layer calls strp_process for each skb to be parsed.
	 */

	if (!sk) {
		if (!cb->lock || !cb->unlock)
			return -EINVAL;
	}

	memset(strp, 0, sizeof(*strp));

	strp->sk = sk;

	strp->cb.lock = cb->lock ? : strp_sock_lock;
	strp->cb.unlock = cb->unlock ? : strp_sock_unlock;
	strp->cb.rcv_msg = cb->rcv_msg;
	strp->cb.parse_msg = cb->parse_msg;
	strp->cb.read_sock_done = cb->read_sock_done ? : default_read_sock_done;
	strp->cb.abort_parser = cb->abort_parser ? : strp_abort_strp;

	INIT_DELAYED_WORK(&strp->msg_timer_work, strp_msg_timeout);
	INIT_WORK(&strp->work, strp_work);

	return 0;
}