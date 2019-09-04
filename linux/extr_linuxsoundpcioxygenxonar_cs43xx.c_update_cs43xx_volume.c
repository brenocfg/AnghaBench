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
struct oxygen {int* dac_volume; } ;

/* Variables and functions */
 int /*<<< orphan*/  cs4398_write_cached (struct oxygen*,int,int) ; 
 int /*<<< orphan*/  update_cs4362a_volumes (struct oxygen*) ; 

__attribute__((used)) static void update_cs43xx_volume(struct oxygen *chip)
{
	cs4398_write_cached(chip, 5, (127 - chip->dac_volume[0]) * 2);
	cs4398_write_cached(chip, 6, (127 - chip->dac_volume[1]) * 2);
	update_cs4362a_volumes(chip);
}