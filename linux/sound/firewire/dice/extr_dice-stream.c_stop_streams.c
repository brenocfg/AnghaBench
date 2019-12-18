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
typedef  int /*<<< orphan*/  u32 ;
struct snd_dice {int dummy; } ;
struct reg_params {unsigned int count; unsigned int size; } ;
typedef  int /*<<< orphan*/  reg ;
typedef  enum amdtp_stream_direction { ____Placeholder_amdtp_stream_direction } amdtp_stream_direction ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int AMDTP_IN_STREAM ; 
 scalar_t__ RX_ISOCHRONOUS ; 
 scalar_t__ TX_ISOCHRONOUS ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_dice_transaction_write_rx (struct snd_dice*,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  snd_dice_transaction_write_tx (struct snd_dice*,scalar_t__,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void stop_streams(struct snd_dice *dice, enum amdtp_stream_direction dir,
			 struct reg_params *params)
{
	__be32 reg;
	unsigned int i;

	for (i = 0; i < params->count; i++) {
		reg = cpu_to_be32((u32)-1);
		if (dir == AMDTP_IN_STREAM) {
			snd_dice_transaction_write_tx(dice,
					params->size * i + TX_ISOCHRONOUS,
					&reg, sizeof(reg));
		} else {
			snd_dice_transaction_write_rx(dice,
					params->size * i + RX_ISOCHRONOUS,
					&reg, sizeof(reg));
		}
	}
}