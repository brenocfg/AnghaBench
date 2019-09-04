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
typedef  int /*<<< orphan*/  u64 ;
struct snd_dice {int /*<<< orphan*/  global_offset; int /*<<< orphan*/  rsrv_offset; int /*<<< orphan*/  sync_offset; int /*<<< orphan*/  rx_offset; int /*<<< orphan*/  tx_offset; } ;
typedef  enum snd_dice_addr_type { ____Placeholder_snd_dice_addr_type } snd_dice_addr_type ;

/* Variables and functions */
 scalar_t__ DICE_PRIVATE_SPACE ; 
#define  SND_DICE_ADDR_TYPE_GLOBAL 132 
#define  SND_DICE_ADDR_TYPE_RSRV 131 
#define  SND_DICE_ADDR_TYPE_RX 130 
#define  SND_DICE_ADDR_TYPE_SYNC 129 
#define  SND_DICE_ADDR_TYPE_TX 128 

__attribute__((used)) static u64 get_subaddr(struct snd_dice *dice, enum snd_dice_addr_type type,
		       u64 offset)
{
	switch (type) {
	case SND_DICE_ADDR_TYPE_TX:
		offset += dice->tx_offset;
		break;
	case SND_DICE_ADDR_TYPE_RX:
		offset += dice->rx_offset;
		break;
	case SND_DICE_ADDR_TYPE_SYNC:
		offset += dice->sync_offset;
		break;
	case SND_DICE_ADDR_TYPE_RSRV:
		offset += dice->rsrv_offset;
		break;
	case SND_DICE_ADDR_TYPE_GLOBAL:
	default:
		offset += dice->global_offset;
		break;
	}
	offset += DICE_PRIVATE_SPACE;
	return offset;
}