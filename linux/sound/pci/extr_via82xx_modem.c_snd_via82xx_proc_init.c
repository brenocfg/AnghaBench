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
struct via82xx_modem {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_card_ro_proc_new (int /*<<< orphan*/ ,char*,struct via82xx_modem*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_via82xx_proc_read ; 

__attribute__((used)) static void snd_via82xx_proc_init(struct via82xx_modem *chip)
{
	snd_card_ro_proc_new(chip->card, "via82xx", chip,
			     snd_via82xx_proc_read);
}