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
typedef  int /*<<< orphan*/  u8 ;
struct rt2x00_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBP4_MAC_IF_CTRL ; 
 int /*<<< orphan*/  rt2800_bbp_read (struct rt2x00_dev*,int) ; 
 int /*<<< orphan*/  rt2800_bbp_write (struct rt2x00_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_set_field8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rt2800_bbp4_mac_if_ctrl(struct rt2x00_dev *rt2x00dev)
{
	u8 value;

	value = rt2800_bbp_read(rt2x00dev, 4);
	rt2x00_set_field8(&value, BBP4_MAC_IF_CTRL, 1);
	rt2800_bbp_write(rt2x00dev, 4, value);
}