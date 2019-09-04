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
struct oxygen {scalar_t__ dac_mute; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM8776_DACMUTE ; 
 int /*<<< orphan*/  WM8776_DMUTE ; 
 int /*<<< orphan*/  wm8776_write_cached (struct oxygen*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_wm8776_mute(struct oxygen *chip)
{
	wm8776_write_cached(chip, WM8776_DACMUTE,
			    chip->dac_mute ? WM8776_DMUTE : 0);
}