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
struct snd_cs4231 {int /*<<< orphan*/  card; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct snd_cs4231* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_card_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cs4231_remove(struct platform_device *op)
{
	struct snd_cs4231 *chip = dev_get_drvdata(&op->dev);

	snd_card_free(chip->card);

	return 0;
}