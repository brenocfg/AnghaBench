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
typedef  int /*<<< orphan*/  u16 ;
struct dpaa2_eth_priv {int num_channels; TYPE_1__** channel; } ;
struct TYPE_2__ {int buf_count; } ;

/* Variables and functions */
 int DPAA2_ETH_BUFS_PER_CMD ; 
 int DPAA2_ETH_NUM_BUFS ; 
 int ENOMEM ; 
 int add_bufs (struct dpaa2_eth_priv*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 

__attribute__((used)) static int seed_pool(struct dpaa2_eth_priv *priv, u16 bpid)
{
	int i, j;
	int new_count;

	/* This is the lazy seeding of Rx buffer pools.
	 * dpaa2_add_bufs() is also used on the Rx hotpath and calls
	 * napi_alloc_frag(). The trouble with that is that it in turn ends up
	 * calling this_cpu_ptr(), which mandates execution in atomic context.
	 * Rather than splitting up the code, do a one-off preempt disable.
	 */
	preempt_disable();
	for (j = 0; j < priv->num_channels; j++) {
		for (i = 0; i < DPAA2_ETH_NUM_BUFS;
		     i += DPAA2_ETH_BUFS_PER_CMD) {
			new_count = add_bufs(priv, priv->channel[j], bpid);
			priv->channel[j]->buf_count += new_count;

			if (new_count < DPAA2_ETH_BUFS_PER_CMD) {
				preempt_enable();
				return -ENOMEM;
			}
		}
	}
	preempt_enable();

	return 0;
}