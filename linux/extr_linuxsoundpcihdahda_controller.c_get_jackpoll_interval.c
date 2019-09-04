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
struct azx {int* jackpoll_ms; size_t dev_index; TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 unsigned int msecs_to_jiffies (int) ; 

__attribute__((used)) static int get_jackpoll_interval(struct azx *chip)
{
	int i;
	unsigned int j;

	if (!chip->jackpoll_ms)
		return 0;

	i = chip->jackpoll_ms[chip->dev_index];
	if (i == 0)
		return 0;
	if (i < 50 || i > 60000)
		j = 0;
	else
		j = msecs_to_jiffies(i);
	if (j == 0)
		dev_warn(chip->card->dev,
			 "jackpoll_ms value out of range: %d\n", i);
	return j;
}