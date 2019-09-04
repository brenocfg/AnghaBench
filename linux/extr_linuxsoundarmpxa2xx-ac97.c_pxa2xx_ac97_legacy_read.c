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
struct snd_ac97 {int /*<<< orphan*/  num; } ;

/* Variables and functions */
 int pxa2xx_ac97_read (int /*<<< orphan*/ ,unsigned short) ; 

__attribute__((used)) static unsigned short pxa2xx_ac97_legacy_read(struct snd_ac97 *ac97,
					      unsigned short reg)
{
	int ret;

	ret = pxa2xx_ac97_read(ac97->num, reg);
	if (ret < 0)
		return 0;
	else
		return (unsigned short)(ret & 0xffff);
}