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
struct rds_ib_connection {int /*<<< orphan*/  i_ack_flags; int /*<<< orphan*/  i_credits; } ;
struct rds_connection {struct rds_ib_connection* c_transport_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_ACK_REQUESTED ; 
 int IB_GET_POST_CREDITS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IB_SET_POST_CREDITS (unsigned int) ; 
 int /*<<< orphan*/  atomic_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void rds_ib_advertise_credits(struct rds_connection *conn, unsigned int posted)
{
	struct rds_ib_connection *ic = conn->c_transport_data;

	if (posted == 0)
		return;

	atomic_add(IB_SET_POST_CREDITS(posted), &ic->i_credits);

	/* Decide whether to send an update to the peer now.
	 * If we would send a credit update for every single buffer we
	 * post, we would end up with an ACK storm (ACK arrives,
	 * consumes buffer, we refill the ring, send ACK to remote
	 * advertising the newly posted buffer... ad inf)
	 *
	 * Performance pretty much depends on how often we send
	 * credit updates - too frequent updates mean lots of ACKs.
	 * Too infrequent updates, and the peer will run out of
	 * credits and has to throttle.
	 * For the time being, 16 seems to be a good compromise.
	 */
	if (IB_GET_POST_CREDITS(atomic_read(&ic->i_credits)) >= 16)
		set_bit(IB_ACK_REQUESTED, &ic->i_ack_flags);
}