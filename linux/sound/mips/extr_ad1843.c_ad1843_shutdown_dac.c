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
struct snd_ad1843 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ad1843_DA1F ; 
 int /*<<< orphan*/  ad1843_DA2F ; 
 int /*<<< orphan*/  ad1843_write_bits (struct snd_ad1843*,int /*<<< orphan*/ *,int) ; 

void ad1843_shutdown_dac(struct snd_ad1843 *ad1843, unsigned int id)
{
	if (id)
		ad1843_write_bits(ad1843, &ad1843_DA2F, 1);
	else
		ad1843_write_bits(ad1843, &ad1843_DA1F, 1);
}