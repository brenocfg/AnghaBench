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
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  msleep (int) ; 
 int snd_rpi_hifiberry_dacplusadc_is_sclk (struct snd_soc_component*) ; 

__attribute__((used)) static bool snd_rpi_hifiberry_dacplusadc_is_sclk_sleep(
	struct snd_soc_component *component)
{
	msleep(2);
	return snd_rpi_hifiberry_dacplusadc_is_sclk(component);
}