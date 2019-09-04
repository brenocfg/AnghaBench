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
struct ieee802154_sub_if_data {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDATA_STATE_RUNNING ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool
ieee802154_sdata_running(struct ieee802154_sub_if_data *sdata)
{
	return test_bit(SDATA_STATE_RUNNING, &sdata->state);
}