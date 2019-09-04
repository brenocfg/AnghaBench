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
struct bdi_writeback_congested {int /*<<< orphan*/  state; } ;
typedef  enum wb_congested_state { ____Placeholder_wb_congested_state } wb_congested_state ;

/* Variables and functions */
 int WB_async_congested ; 
 int WB_sync_congested ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nr_wb_congested ; 
 int /*<<< orphan*/  test_and_set_bit (int,int /*<<< orphan*/ *) ; 

void set_wb_congested(struct bdi_writeback_congested *congested, int sync)
{
	enum wb_congested_state bit;

	bit = sync ? WB_sync_congested : WB_async_congested;
	if (!test_and_set_bit(bit, &congested->state))
		atomic_inc(&nr_wb_congested[sync]);
}