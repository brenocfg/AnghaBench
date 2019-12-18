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
struct snd_opl3sa2 {scalar_t__ irq; int /*<<< orphan*/  res_port; } ;
struct snd_card {struct snd_opl3sa2* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,struct snd_card*) ; 
 int /*<<< orphan*/  release_and_free_resource (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_opl3sa2_free(struct snd_card *card)
{
	struct snd_opl3sa2 *chip = card->private_data;
	if (chip->irq >= 0)
		free_irq(chip->irq, card);
	release_and_free_resource(chip->res_port);
}