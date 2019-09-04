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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct dim_channel {scalar_t__ dbr_addr; scalar_t__ dbr_size; int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dim_is_initialized; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBR_BLOCK_SIZE ; 
 scalar_t__ DBR_SIZE ; 
 int /*<<< orphan*/  DIM_ERR_DRIVER_NOT_INITIALIZED ; 
 int /*<<< orphan*/  DIM_INIT_ERR_CHANNEL_ADDRESS ; 
 int /*<<< orphan*/  DIM_INIT_ERR_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  DIM_NO_ERROR ; 
 scalar_t__ ROUND_UP_TO (int,int /*<<< orphan*/ ) ; 
 scalar_t__ alloc_dbr (scalar_t__) ; 
 int /*<<< orphan*/  channel_init (struct dim_channel*,int) ; 
 int /*<<< orphan*/  check_channel_address (int) ; 
 int /*<<< orphan*/  dim2_configure_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__ g ; 

__attribute__((used)) static u8 init_ctrl_async(struct dim_channel *ch, u8 type, u8 is_tx,
			  u16 ch_address, u16 hw_buffer_size)
{
	if (!g.dim_is_initialized || !ch)
		return DIM_ERR_DRIVER_NOT_INITIALIZED;

	if (!check_channel_address(ch_address))
		return DIM_INIT_ERR_CHANNEL_ADDRESS;

	if (!ch->dbr_size)
		ch->dbr_size = ROUND_UP_TO(hw_buffer_size, DBR_BLOCK_SIZE);
	ch->dbr_addr = alloc_dbr(ch->dbr_size);
	if (ch->dbr_addr >= DBR_SIZE)
		return DIM_INIT_ERR_OUT_OF_MEMORY;

	channel_init(ch, ch_address / 2);

	dim2_configure_channel(ch->addr, type, is_tx,
			       ch->dbr_addr, ch->dbr_size, 0);

	return DIM_NO_ERROR;
}