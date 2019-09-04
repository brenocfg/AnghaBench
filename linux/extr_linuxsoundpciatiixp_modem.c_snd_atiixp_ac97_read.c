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
struct snd_ac97 {int /*<<< orphan*/  num; struct atiixp_modem* private_data; } ;
struct atiixp_modem {int dummy; } ;

/* Variables and functions */
 unsigned short snd_atiixp_codec_read (struct atiixp_modem*,int /*<<< orphan*/ ,unsigned short) ; 

__attribute__((used)) static unsigned short snd_atiixp_ac97_read(struct snd_ac97 *ac97,
					   unsigned short reg)
{
	struct atiixp_modem *chip = ac97->private_data;
	return snd_atiixp_codec_read(chip, ac97->num, reg);
    
}