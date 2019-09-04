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
 int pxa2xx_ac97_write (int /*<<< orphan*/ ,unsigned short,unsigned short) ; 

__attribute__((used)) static void pxa2xx_ac97_legacy_write(struct snd_ac97 *ac97,
				     unsigned short reg, unsigned short val)
{
	int ret;

	ret = pxa2xx_ac97_write(ac97->num, reg, val);
}