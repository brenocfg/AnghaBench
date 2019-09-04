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
struct hdac_device {int dummy; } ;

/* Variables and functions */
 int snd_hdac_keep_power_up (struct hdac_device*) ; 

__attribute__((used)) static int codec_pm_lock(struct hdac_device *codec)
{
	return snd_hdac_keep_power_up(codec);
}