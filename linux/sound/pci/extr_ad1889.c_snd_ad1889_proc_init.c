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
struct snd_ad1889 {TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_ad1889_proc_read ; 
 int /*<<< orphan*/  snd_card_ro_proc_new (TYPE_1__*,int /*<<< orphan*/ ,struct snd_ad1889*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
snd_ad1889_proc_init(struct snd_ad1889 *chip)
{
	snd_card_ro_proc_new(chip->card, chip->card->driver,
			     chip, snd_ad1889_proc_read);
}