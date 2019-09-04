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
typedef  int u32 ;
struct regmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_IC_CODEC_CTRL1 ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void enable_and_reset_codec(struct regmap *regmap,
		u32 codec_enable_bits, u32 codec_reset_bits)
{
	regmap_update_bits(regmap, AUDIO_IC_CODEC_CTRL1,
			codec_enable_bits | codec_reset_bits,
			codec_enable_bits);
	msleep(20);
	regmap_update_bits(regmap, AUDIO_IC_CODEC_CTRL1,
			codec_reset_bits, codec_reset_bits);
}