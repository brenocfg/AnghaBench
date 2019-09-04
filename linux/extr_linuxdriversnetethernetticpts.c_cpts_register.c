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
struct cpts {int /*<<< orphan*/  refclk; int /*<<< orphan*/  ov_check_period; int /*<<< orphan*/ * clock; int /*<<< orphan*/  phc_index; int /*<<< orphan*/  dev; int /*<<< orphan*/  info; int /*<<< orphan*/  cc; int /*<<< orphan*/  tc; int /*<<< orphan*/  pool; TYPE_1__* pool_data; int /*<<< orphan*/  events; int /*<<< orphan*/  txq; } ;
struct TYPE_2__ {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPTS_EN ; 
 int CPTS_MAX_EVENTS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TS_PEND_EN ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  control ; 
 int /*<<< orphan*/  cpts_write32 (struct cpts*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  int_enable ; 
 int /*<<< orphan*/  ktime_get_real () ; 
 int /*<<< orphan*/  ktime_to_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptp_clock_index (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ptp_clock_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptp_schedule_worker (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timecounter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int cpts_register(struct cpts *cpts)
{
	int err, i;

	skb_queue_head_init(&cpts->txq);
	INIT_LIST_HEAD(&cpts->events);
	INIT_LIST_HEAD(&cpts->pool);
	for (i = 0; i < CPTS_MAX_EVENTS; i++)
		list_add(&cpts->pool_data[i].list, &cpts->pool);

	clk_enable(cpts->refclk);

	cpts_write32(cpts, CPTS_EN, control);
	cpts_write32(cpts, TS_PEND_EN, int_enable);

	timecounter_init(&cpts->tc, &cpts->cc, ktime_to_ns(ktime_get_real()));

	cpts->clock = ptp_clock_register(&cpts->info, cpts->dev);
	if (IS_ERR(cpts->clock)) {
		err = PTR_ERR(cpts->clock);
		cpts->clock = NULL;
		goto err_ptp;
	}
	cpts->phc_index = ptp_clock_index(cpts->clock);

	ptp_schedule_worker(cpts->clock, cpts->ov_check_period);
	return 0;

err_ptp:
	clk_disable(cpts->refclk);
	return err;
}