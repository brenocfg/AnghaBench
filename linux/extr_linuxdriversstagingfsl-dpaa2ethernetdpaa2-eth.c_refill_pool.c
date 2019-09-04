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
typedef  int /*<<< orphan*/  u16 ;
struct dpaa2_eth_priv {int dummy; } ;
struct dpaa2_eth_channel {scalar_t__ buf_count; } ;

/* Variables and functions */
 scalar_t__ DPAA2_ETH_NUM_BUFS ; 
 scalar_t__ DPAA2_ETH_REFILL_THRESH ; 
 int ENOMEM ; 
 int add_bufs (struct dpaa2_eth_priv*,struct dpaa2_eth_channel*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int refill_pool(struct dpaa2_eth_priv *priv,
		       struct dpaa2_eth_channel *ch,
		       u16 bpid)
{
	int new_count;

	if (likely(ch->buf_count >= DPAA2_ETH_REFILL_THRESH))
		return 0;

	do {
		new_count = add_bufs(priv, ch, bpid);
		if (unlikely(!new_count)) {
			/* Out of memory; abort for now, we'll try later on */
			break;
		}
		ch->buf_count += new_count;
	} while (ch->buf_count < DPAA2_ETH_NUM_BUFS);

	if (unlikely(ch->buf_count < DPAA2_ETH_NUM_BUFS))
		return -ENOMEM;

	return 0;
}