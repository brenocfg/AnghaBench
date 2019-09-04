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
struct ti_bandgap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COUNTER ; 
 int /*<<< orphan*/  COUNTER_DELAY ; 
 int ENOTSUPP ; 
 scalar_t__ TI_BANDGAP_HAS (struct ti_bandgap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_bandgap_read_counter (struct ti_bandgap*,int,int*) ; 
 int /*<<< orphan*/  ti_bandgap_read_counter_delay (struct ti_bandgap*,int,int*) ; 
 int ti_bandgap_validate (struct ti_bandgap*,int) ; 

int ti_bandgap_read_update_interval(struct ti_bandgap *bgp, int id,
				    int *interval)
{
	int ret = 0;

	ret = ti_bandgap_validate(bgp, id);
	if (ret)
		goto exit;

	if (!TI_BANDGAP_HAS(bgp, COUNTER) &&
	    !TI_BANDGAP_HAS(bgp, COUNTER_DELAY)) {
		ret = -ENOTSUPP;
		goto exit;
	}

	if (TI_BANDGAP_HAS(bgp, COUNTER)) {
		ti_bandgap_read_counter(bgp, id, interval);
		goto exit;
	}

	ti_bandgap_read_counter_delay(bgp, id, interval);
exit:
	return ret;
}