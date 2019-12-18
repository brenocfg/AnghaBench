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
struct snd_pcsp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pcsp_sync_stop (struct snd_pcsp*) ; 
 int /*<<< orphan*/  pcspkr_stop_sound () ; 

__attribute__((used)) static void pcsp_stop_beep(struct snd_pcsp *chip)
{
	pcsp_sync_stop(chip);
	pcspkr_stop_sound();
}