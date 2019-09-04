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
struct snd_ali {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALI_REG (struct snd_ali*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ALI_SCTRL ; 
 unsigned char ALI_SPDIF_OUT_ENABLE ; 
 unsigned char inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ali_disable_spdif_chnout (struct snd_ali*) ; 

__attribute__((used)) static void snd_ali_disable_spdif_out(struct snd_ali *codec)
{
	unsigned char  bVal;

	bVal = inb(ALI_REG(codec, ALI_SCTRL));
	outb(bVal & ~ALI_SPDIF_OUT_ENABLE, ALI_REG(codec, ALI_SCTRL));

	snd_ali_disable_spdif_chnout(codec);
}