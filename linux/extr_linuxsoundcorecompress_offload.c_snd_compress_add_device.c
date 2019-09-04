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
struct snd_compr {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int snd_card_register (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_compress_add_device(struct snd_compr *device)
{
	int ret;

	if (!device->card)
		return -EINVAL;

	/* register the card */
	ret = snd_card_register(device->card);
	if (ret)
		goto out;
	return 0;

out:
	pr_err("failed with %d\n", ret);
	return ret;

}