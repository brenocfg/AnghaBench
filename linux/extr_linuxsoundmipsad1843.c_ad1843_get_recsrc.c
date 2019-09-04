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
 int /*<<< orphan*/  ad1843_LSS ; 
 int /*<<< orphan*/  ad1843_RSS ; 
 int ad1843_read_bits (struct snd_ad1843*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ad1843_write_multi (struct snd_ad1843*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 

int ad1843_get_recsrc(struct snd_ad1843 *ad1843)
{
	int val = ad1843_read_bits(ad1843, &ad1843_LSS);

	if (val < 0 || val > 2) {
		val = 2;
		ad1843_write_multi(ad1843, 2,
				   &ad1843_LSS, val, &ad1843_RSS, val);
	}
	return val;
}