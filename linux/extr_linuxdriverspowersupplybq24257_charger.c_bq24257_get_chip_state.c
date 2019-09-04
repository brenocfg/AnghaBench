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
struct bq24257_state {int status; int fault; int power_good; } ;
struct bq24257_device {scalar_t__ pg; } ;

/* Variables and functions */
#define  FAULT_INPUT_LDO_LOW 130 
#define  FAULT_INPUT_OVP 129 
#define  FAULT_INPUT_UVLO 128 
 int /*<<< orphan*/  F_FAULT ; 
 int /*<<< orphan*/  F_STAT ; 
 int bq24257_field_read (struct bq24257_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_get_value_cansleep (scalar_t__) ; 

__attribute__((used)) static int bq24257_get_chip_state(struct bq24257_device *bq,
				  struct bq24257_state *state)
{
	int ret;

	ret = bq24257_field_read(bq, F_STAT);
	if (ret < 0)
		return ret;

	state->status = ret;

	ret = bq24257_field_read(bq, F_FAULT);
	if (ret < 0)
		return ret;

	state->fault = ret;

	if (bq->pg)
		state->power_good = !gpiod_get_value_cansleep(bq->pg);
	else
		/*
		 * If we have a chip without a dedicated power-good GPIO or
		 * some other explicit bit that would provide this information
		 * assume the power is good if there is no supply related
		 * fault - and not good otherwise. There is a possibility for
		 * other errors to mask that power in fact is not good but this
		 * is probably the best we can do here.
		 */
		switch (state->fault) {
		case FAULT_INPUT_OVP:
		case FAULT_INPUT_UVLO:
		case FAULT_INPUT_LDO_LOW:
			state->power_good = false;
			break;
		default:
			state->power_good = true;
		}

	return 0;
}