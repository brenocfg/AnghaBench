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
struct hw {int dummy; } ;
struct daio_mgr_ctrl_blk {void** rxctl; void** txctl; } ;

/* Variables and functions */
 scalar_t__ AUDIO_IO_RX_CTL ; 
 scalar_t__ AUDIO_IO_TX_CTL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* hw_read_20kx (struct hw*,scalar_t__) ; 
 struct daio_mgr_ctrl_blk* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int daio_mgr_get_ctrl_blk(struct hw *hw, void **rblk)
{
	struct daio_mgr_ctrl_blk *blk;
	int i;

	*rblk = NULL;
	blk = kzalloc(sizeof(*blk), GFP_KERNEL);
	if (!blk)
		return -ENOMEM;

	for (i = 0; i < 8; i++) {
		blk->txctl[i] = hw_read_20kx(hw, AUDIO_IO_TX_CTL+(0x40*i));
		blk->rxctl[i] = hw_read_20kx(hw, AUDIO_IO_RX_CTL+(0x40*i));
	}

	*rblk = blk;

	return 0;
}