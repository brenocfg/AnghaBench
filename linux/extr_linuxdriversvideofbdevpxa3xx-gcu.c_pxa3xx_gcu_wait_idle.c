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
typedef  scalar_t__ u32 ;
struct pxa3xx_gcu_priv {TYPE_1__* shared; int /*<<< orphan*/  wait_idle; } ;
struct TYPE_2__ {int num_interrupts; scalar_t__ hw_running; int /*<<< orphan*/  num_wait_idle; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int HZ ; 
 int /*<<< orphan*/  QDUMP (char*) ; 
 int /*<<< orphan*/  QERROR (char*) ; 
 int /*<<< orphan*/  REG_GCRBEXHR ; 
 scalar_t__ gc_readl (struct pxa3xx_gcu_priv*,int /*<<< orphan*/ ) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
pxa3xx_gcu_wait_idle(struct pxa3xx_gcu_priv *priv)
{
	int ret = 0;

	QDUMP("Waiting for idle...");

	/* Does not need to be atomic. There's a lock in user space,
	 * but anyhow, this is just for statistics. */
	priv->shared->num_wait_idle++;

	while (priv->shared->hw_running) {
		int num = priv->shared->num_interrupts;
		u32 rbexhr = gc_readl(priv, REG_GCRBEXHR);

		ret = wait_event_interruptible_timeout(priv->wait_idle,
					!priv->shared->hw_running, HZ*4);

		if (ret != 0)
			break;

		if (gc_readl(priv, REG_GCRBEXHR) == rbexhr &&
		    priv->shared->num_interrupts == num) {
			QERROR("TIMEOUT");
			ret = -ETIMEDOUT;
			break;
		}
	}

	QDUMP("done");

	return ret;
}