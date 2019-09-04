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
struct tsi108_prv_data {int /*<<< orphan*/  napi; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TSI108_EC_INTMASK ; 
 int TSI108_INT_RXERROR ; 
 int TSI108_INT_RXOVERRUN ; 
 int TSI108_INT_RXQUEUE0 ; 
 int TSI108_INT_RXTHRESH ; 
 int TSI108_INT_RXWAIT ; 
 int TSI_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TSI_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __napi_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ napi_schedule_prep (int /*<<< orphan*/ *) ; 
 struct tsi108_prv_data* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 

__attribute__((used)) static void tsi108_rx_int(struct net_device *dev)
{
	struct tsi108_prv_data *data = netdev_priv(dev);

	/* A race could cause dev to already be scheduled, so it's not an
	 * error if that happens (and interrupts shouldn't be re-masked,
	 * because that can cause harmful races, if poll has already
	 * unmasked them but not cleared LINK_STATE_SCHED).
	 *
	 * This can happen if this code races with tsi108_poll(), which masks
	 * the interrupts after tsi108_irq_one() read the mask, but before
	 * napi_schedule is called.  It could also happen due to calls
	 * from tsi108_check_rxring().
	 */

	if (napi_schedule_prep(&data->napi)) {
		/* Mask, rather than ack, the receive interrupts.  The ack
		 * will happen in tsi108_poll().
		 */

		TSI_WRITE(TSI108_EC_INTMASK,
				     TSI_READ(TSI108_EC_INTMASK) |
				     TSI108_INT_RXQUEUE0
				     | TSI108_INT_RXTHRESH |
				     TSI108_INT_RXOVERRUN | TSI108_INT_RXERROR |
				     TSI108_INT_RXWAIT);
		__napi_schedule(&data->napi);
	} else {
		if (!netif_running(dev)) {
			/* This can happen if an interrupt occurs while the
			 * interface is being brought down, as the START
			 * bit is cleared before the stop function is called.
			 *
			 * In this case, the interrupts must be masked, or
			 * they will continue indefinitely.
			 *
			 * There's a race here if the interface is brought down
			 * and then up in rapid succession, as the device could
			 * be made running after the above check and before
			 * the masking below.  This will only happen if the IRQ
			 * thread has a lower priority than the task brining
			 * up the interface.  Fixing this race would likely
			 * require changes in generic code.
			 */

			TSI_WRITE(TSI108_EC_INTMASK,
					     TSI_READ
					     (TSI108_EC_INTMASK) |
					     TSI108_INT_RXQUEUE0 |
					     TSI108_INT_RXTHRESH |
					     TSI108_INT_RXOVERRUN |
					     TSI108_INT_RXERROR |
					     TSI108_INT_RXWAIT);
		}
	}
}