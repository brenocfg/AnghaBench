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
struct snd_pmac {int hp_stat_mask; TYPE_1__* awacs; } ;
struct TYPE_2__ {int /*<<< orphan*/  codec_stat; } ;

/* Variables and functions */
 int in_le32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_pmac_awacs_detect_headphone(struct snd_pmac *chip)
{
	return (in_le32(&chip->awacs->codec_stat) & chip->hp_stat_mask) ? 1 : 0;
}