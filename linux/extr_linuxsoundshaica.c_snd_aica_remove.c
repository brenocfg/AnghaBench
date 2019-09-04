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
struct snd_card_aica {int /*<<< orphan*/  card; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  kfree (struct snd_card_aica*) ; 
 struct snd_card_aica* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  snd_card_free (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int snd_aica_remove(struct platform_device *devptr)
{
	struct snd_card_aica *dreamcastcard;
	dreamcastcard = platform_get_drvdata(devptr);
	if (unlikely(!dreamcastcard))
		return -ENODEV;
	snd_card_free(dreamcastcard->card);
	kfree(dreamcastcard);
	return 0;
}