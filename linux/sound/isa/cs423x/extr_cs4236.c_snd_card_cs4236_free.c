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
struct snd_card_cs4236 {int /*<<< orphan*/  res_sb_port; } ;
struct snd_card {struct snd_card_cs4236* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  release_and_free_resource (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_card_cs4236_free(struct snd_card *card)
{
	struct snd_card_cs4236 *acard = card->private_data;

	release_and_free_resource(acard->res_sb_port);
}