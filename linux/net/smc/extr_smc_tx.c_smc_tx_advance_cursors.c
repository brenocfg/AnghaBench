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
typedef  union smc_host_cursor {int dummy; } smc_host_cursor ;
struct smc_connection {TYPE_1__* sndbuf_desc; int /*<<< orphan*/  peer_rmbe_space; int /*<<< orphan*/  peer_rmbe_size; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_sub (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smc_curs_add (int /*<<< orphan*/ ,union smc_host_cursor*,size_t) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  smp_mb__before_atomic () ; 

__attribute__((used)) static inline void smc_tx_advance_cursors(struct smc_connection *conn,
					  union smc_host_cursor *prod,
					  union smc_host_cursor *sent,
					  size_t len)
{
	smc_curs_add(conn->peer_rmbe_size, prod, len);
	/* increased in recv tasklet smc_cdc_msg_rcv() */
	smp_mb__before_atomic();
	/* data in flight reduces usable snd_wnd */
	atomic_sub(len, &conn->peer_rmbe_space);
	/* guarantee 0 <= peer_rmbe_space <= peer_rmbe_size */
	smp_mb__after_atomic();
	smc_curs_add(conn->sndbuf_desc->len, sent, len);
}