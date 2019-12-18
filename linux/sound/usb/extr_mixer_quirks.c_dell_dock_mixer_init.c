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
struct usb_mixer_interface {int /*<<< orphan*/  chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  dell_dock_init_vol (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int dell_dock_mixer_init(struct usb_mixer_interface *mixer)
{
	/* fix to 0dB playback volumes */
	dell_dock_init_vol(mixer->chip, 1, 16);
	dell_dock_init_vol(mixer->chip, 2, 16);
	dell_dock_init_vol(mixer->chip, 1, 19);
	dell_dock_init_vol(mixer->chip, 2, 19);
	return 0;
}