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
struct cw1200_common {int /*<<< orphan*/ * tx_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  cw1200_queue_lock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void cw1200_tx_queues_lock(struct cw1200_common *priv)
{
	int i;
	for (i = 0; i < 4; ++i)
		cw1200_queue_lock(&priv->tx_queue[i]);
}