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
struct es1968 {int /*<<< orphan*/ * apu; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESM_APU_FREE ; 

__attribute__((used)) static void snd_es1968_free_apu_pair(struct es1968 *chip, int apu)
{
	chip->apu[apu] = chip->apu[apu + 1] = ESM_APU_FREE;
}