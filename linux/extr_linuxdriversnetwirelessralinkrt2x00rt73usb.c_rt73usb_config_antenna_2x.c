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
struct antenna_setup {int rx; } ;

/* Variables and functions */
#define  ANTENNA_A 130 
#define  ANTENNA_B 129 
#define  ANTENNA_HW_DIVERSITY 128 
 int /*<<< orphan*/  BBP_R3_SMART_MODE ; 
 int /*<<< orphan*/  BBP_R4_RX_ANTENNA_CONTROL ; 
 int /*<<< orphan*/  BBP_R4_RX_FRAME_END ; 
 int /*<<< orphan*/  BBP_R77_RX_ANTENNA ; 
 int /*<<< orphan*/  rt2x00_has_cap_frame_type (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00_set_field8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt73usb_bbp_read (struct rt2x00_dev*,int) ; 
 int /*<<< orphan*/  rt73usb_bbp_write (struct rt2x00_dev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rt73usb_config_antenna_2x(struct rt2x00_dev *rt2x00dev,
				      struct antenna_setup *ant)
{
	u8 r3;
	u8 r4;
	u8 r77;

	r3 = rt73usb_bbp_read(rt2x00dev, 3);
	r4 = rt73usb_bbp_read(rt2x00dev, 4);
	r77 = rt73usb_bbp_read(rt2x00dev, 77);

	rt2x00_set_field8(&r3, BBP_R3_SMART_MODE, 0);
	rt2x00_set_field8(&r4, BBP_R4_RX_FRAME_END,
			  !rt2x00_has_cap_frame_type(rt2x00dev));

	/*
	 * Configure the RX antenna.
	 */
	switch (ant->rx) {
	case ANTENNA_HW_DIVERSITY:
		rt2x00_set_field8(&r4, BBP_R4_RX_ANTENNA_CONTROL, 2);
		break;
	case ANTENNA_A:
		rt2x00_set_field8(&r77, BBP_R77_RX_ANTENNA, 3);
		rt2x00_set_field8(&r4, BBP_R4_RX_ANTENNA_CONTROL, 1);
		break;
	case ANTENNA_B:
	default:
		rt2x00_set_field8(&r77, BBP_R77_RX_ANTENNA, 0);
		rt2x00_set_field8(&r4, BBP_R4_RX_ANTENNA_CONTROL, 1);
		break;
	}

	rt73usb_bbp_write(rt2x00dev, 77, r77);
	rt73usb_bbp_write(rt2x00dev, 3, r3);
	rt73usb_bbp_write(rt2x00dev, 4, r4);
}