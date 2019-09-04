#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int dma_addr_t ;
struct TYPE_5__ {int* command_packet_phys; scalar_t__ posted_request_count; scalar_t__ max_posted_request_count; int /*<<< orphan*/ * state; } ;
typedef  TYPE_1__ TW_Device_Extension ;

/* Variables and functions */
 int /*<<< orphan*/  TWL_HIBQPH_REG_ADDR (TYPE_1__*) ; 
 int /*<<< orphan*/  TWL_HIBQPL_REG_ADDR (TYPE_1__*) ; 
 int TWL_PULL_MODE ; 
 scalar_t__ TW_COMMAND_OFFSET ; 
 int /*<<< orphan*/  TW_S_POSTED ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl_post_command_packet(TW_Device_Extension *tw_dev, int request_id)
{
	dma_addr_t command_que_value;

	command_que_value = tw_dev->command_packet_phys[request_id];
	command_que_value += TW_COMMAND_OFFSET;

	/* First write upper 4 bytes */
	writel((u32)((u64)command_que_value >> 32), TWL_HIBQPH_REG_ADDR(tw_dev));
	/* Then the lower 4 bytes */
	writel((u32)(command_que_value | TWL_PULL_MODE), TWL_HIBQPL_REG_ADDR(tw_dev));

	tw_dev->state[request_id] = TW_S_POSTED;
	tw_dev->posted_request_count++;
	if (tw_dev->posted_request_count > tw_dev->max_posted_request_count)
		tw_dev->max_posted_request_count = tw_dev->posted_request_count;

	return 0;
}