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
struct mii_bus {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int max_adj; int /*<<< orphan*/  pin_config; int /*<<< orphan*/  verify; int /*<<< orphan*/  enable; int /*<<< orphan*/  settime64; int /*<<< orphan*/  gettime64; int /*<<< orphan*/  adjtime; int /*<<< orphan*/  adjfine; scalar_t__ pps; int /*<<< orphan*/  n_pins; int /*<<< orphan*/  n_per_out; int /*<<< orphan*/  n_ext_ts; scalar_t__ n_alarm; int /*<<< orphan*/  name; int /*<<< orphan*/  owner; } ;
struct dp83640_clock {TYPE_1__ caps; int /*<<< orphan*/  phylist; int /*<<< orphan*/  clock_lock; int /*<<< orphan*/  extreg_lock; struct mii_bus* bus; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP83640_N_PINS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  N_EXT_TS ; 
 int /*<<< orphan*/  N_PER_OUT ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dp83640_gpio_defaults (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptp_dp83640_adjfine ; 
 int /*<<< orphan*/  ptp_dp83640_adjtime ; 
 int /*<<< orphan*/  ptp_dp83640_enable ; 
 int /*<<< orphan*/  ptp_dp83640_gettime ; 
 int /*<<< orphan*/  ptp_dp83640_settime ; 
 int /*<<< orphan*/  ptp_dp83640_verify ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void dp83640_clock_init(struct dp83640_clock *clock, struct mii_bus *bus)
{
	INIT_LIST_HEAD(&clock->list);
	clock->bus = bus;
	mutex_init(&clock->extreg_lock);
	mutex_init(&clock->clock_lock);
	INIT_LIST_HEAD(&clock->phylist);
	clock->caps.owner = THIS_MODULE;
	sprintf(clock->caps.name, "dp83640 timer");
	clock->caps.max_adj	= 1953124;
	clock->caps.n_alarm	= 0;
	clock->caps.n_ext_ts	= N_EXT_TS;
	clock->caps.n_per_out	= N_PER_OUT;
	clock->caps.n_pins	= DP83640_N_PINS;
	clock->caps.pps		= 0;
	clock->caps.adjfine	= ptp_dp83640_adjfine;
	clock->caps.adjtime	= ptp_dp83640_adjtime;
	clock->caps.gettime64	= ptp_dp83640_gettime;
	clock->caps.settime64	= ptp_dp83640_settime;
	clock->caps.enable	= ptp_dp83640_enable;
	clock->caps.verify	= ptp_dp83640_verify;
	/*
	 * Convert the module param defaults into a dynamic pin configuration.
	 */
	dp83640_gpio_defaults(clock->caps.pin_config);
	/*
	 * Get a reference to this bus instance.
	 */
	get_device(&bus->dev);
}