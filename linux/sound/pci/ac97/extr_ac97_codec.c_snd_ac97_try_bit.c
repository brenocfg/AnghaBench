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
struct snd_ac97 {int dummy; } ;

/* Variables and functions */
 unsigned short snd_ac97_read (struct snd_ac97*,int) ; 
 int /*<<< orphan*/  snd_ac97_write (struct snd_ac97*,int,unsigned short) ; 
 int /*<<< orphan*/  snd_ac97_write_cache (struct snd_ac97*,int,unsigned short) ; 

__attribute__((used)) static int snd_ac97_try_bit(struct snd_ac97 * ac97, int reg, int bit)
{
	unsigned short mask, val, orig, res;

	mask = 1 << bit;
	orig = snd_ac97_read(ac97, reg);
	val = orig ^ mask;
	snd_ac97_write(ac97, reg, val);
	res = snd_ac97_read(ac97, reg);
	snd_ac97_write_cache(ac97, reg, orig);
	return res == val;
}