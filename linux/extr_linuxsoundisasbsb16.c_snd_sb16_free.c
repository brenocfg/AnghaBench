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
struct snd_card_sb16 {int /*<<< orphan*/  fm_res; } ;
struct snd_card {struct snd_card_sb16* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  release_and_free_resource (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_sb16_free(struct snd_card *card)
{
	struct snd_card_sb16 *acard = card->private_data;
        
	if (acard == NULL)
		return;
	release_and_free_resource(acard->fm_res);
}