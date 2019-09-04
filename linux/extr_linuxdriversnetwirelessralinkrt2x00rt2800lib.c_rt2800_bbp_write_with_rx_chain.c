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
typedef  scalar_t__ u8 ;
struct TYPE_2__ {scalar_t__ rx_chain_num; } ;
struct rt2x00_dev {TYPE_1__ default_ant; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBP27_RX_CHAIN_SEL ; 
 scalar_t__ rt2800_bbp_read (struct rt2x00_dev*,int) ; 
 int /*<<< orphan*/  rt2800_bbp_write (struct rt2x00_dev*,unsigned int const,scalar_t__ const) ; 
 int /*<<< orphan*/  rt2x00_set_field8 (scalar_t__*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void rt2800_bbp_write_with_rx_chain(struct rt2x00_dev *rt2x00dev,
					   const unsigned int word,
					   const u8 value)
{
	u8 chain, reg;

	for (chain = 0; chain < rt2x00dev->default_ant.rx_chain_num; chain++) {
		reg = rt2800_bbp_read(rt2x00dev, 27);
		rt2x00_set_field8(&reg,  BBP27_RX_CHAIN_SEL, chain);
		rt2800_bbp_write(rt2x00dev, 27, reg);

		rt2800_bbp_write(rt2x00dev, word, value);
	}
}