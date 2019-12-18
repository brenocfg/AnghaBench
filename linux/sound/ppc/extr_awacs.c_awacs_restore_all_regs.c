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
struct snd_pmac {scalar_t__ model; int /*<<< orphan*/ * awacs_reg; } ;

/* Variables and functions */
 scalar_t__ PMAC_SCREAMER ; 
 int /*<<< orphan*/  snd_pmac_awacs_write_noreg (struct snd_pmac*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void awacs_restore_all_regs(struct snd_pmac *chip)
{
	snd_pmac_awacs_write_noreg(chip, 0, chip->awacs_reg[0]);
	snd_pmac_awacs_write_noreg(chip, 1, chip->awacs_reg[1]);
	snd_pmac_awacs_write_noreg(chip, 2, chip->awacs_reg[2]);
	snd_pmac_awacs_write_noreg(chip, 4, chip->awacs_reg[4]);
	if (chip->model == PMAC_SCREAMER) {
		snd_pmac_awacs_write_noreg(chip, 5, chip->awacs_reg[5]);
		snd_pmac_awacs_write_noreg(chip, 6, chip->awacs_reg[6]);
		snd_pmac_awacs_write_noreg(chip, 7, chip->awacs_reg[7]);
	}
}