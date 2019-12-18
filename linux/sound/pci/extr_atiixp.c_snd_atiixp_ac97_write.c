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
struct snd_ac97 {int /*<<< orphan*/  num; struct atiixp* private_data; } ;
struct atiixp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_atiixp_codec_write (struct atiixp*,int /*<<< orphan*/ ,unsigned short,unsigned short) ; 

__attribute__((used)) static void snd_atiixp_ac97_write(struct snd_ac97 *ac97, unsigned short reg,
				  unsigned short val)
{
	struct atiixp *chip = ac97->private_data;
	snd_atiixp_codec_write(chip, ac97->num, reg, val);
}