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
struct snd_card {struct isight* private_data; } ;
struct isight {int /*<<< orphan*/  resources; } ;

/* Variables and functions */
 int /*<<< orphan*/  fw_iso_resources_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void isight_card_free(struct snd_card *card)
{
	struct isight *isight = card->private_data;

	fw_iso_resources_destroy(&isight->resources);
}