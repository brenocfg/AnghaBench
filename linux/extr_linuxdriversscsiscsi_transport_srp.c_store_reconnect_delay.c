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
struct srp_rport {int reconnect_delay; scalar_t__ state; int /*<<< orphan*/  reconnect_work; int /*<<< orphan*/  dev_loss_tmo; int /*<<< orphan*/  fast_io_fail_tmo; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ SRP_RPORT_RUNNING ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int srp_parse_tmo (int*,char const*) ; 
 int srp_tmo_valid (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  system_long_wq ; 
 struct srp_rport* transport_class_to_srp_rport (struct device*) ; 

__attribute__((used)) static ssize_t store_reconnect_delay(struct device *dev,
				     struct device_attribute *attr,
				     const char *buf, const size_t count)
{
	struct srp_rport *rport = transport_class_to_srp_rport(dev);
	int res, delay;

	res = srp_parse_tmo(&delay, buf);
	if (res)
		goto out;
	res = srp_tmo_valid(delay, rport->fast_io_fail_tmo,
			    rport->dev_loss_tmo);
	if (res)
		goto out;

	if (rport->reconnect_delay <= 0 && delay > 0 &&
	    rport->state != SRP_RPORT_RUNNING) {
		queue_delayed_work(system_long_wq, &rport->reconnect_work,
				   delay * HZ);
	} else if (delay <= 0) {
		cancel_delayed_work(&rport->reconnect_work);
	}
	rport->reconnect_delay = delay;
	res = count;

out:
	return res;
}