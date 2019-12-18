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
struct ensoniq {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_card_ro_proc_new (int /*<<< orphan*/ ,char*,struct ensoniq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ensoniq_proc_read ; 

__attribute__((used)) static void snd_ensoniq_proc_init(struct ensoniq *ensoniq)
{
	snd_card_ro_proc_new(ensoniq->card, "audiopci", ensoniq,
			     snd_ensoniq_proc_read);
}