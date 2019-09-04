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
struct snd_card {struct aaci* private_data; } ;
struct amba_device {int dummy; } ;
struct aaci {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ AACI_MAINCR ; 
 struct snd_card* amba_get_drvdata (struct amba_device*) ; 
 int /*<<< orphan*/  amba_release_regions (struct amba_device*) ; 
 int /*<<< orphan*/  snd_card_free (struct snd_card*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int aaci_remove(struct amba_device *dev)
{
	struct snd_card *card = amba_get_drvdata(dev);

	if (card) {
		struct aaci *aaci = card->private_data;
		writel(0, aaci->base + AACI_MAINCR);

		snd_card_free(card);
		amba_release_regions(dev);
	}

	return 0;
}