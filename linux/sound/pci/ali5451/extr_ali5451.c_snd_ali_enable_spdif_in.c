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
 int /*<<< orphan*/  ALI_GLOBAL_CONTROL ; 
 int /*<<< orphan*/  ALI_REG (struct snd_ali*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ALI_SPDIF_CTRL ; 
 int /*<<< orphan*/  ALI_SPDIF_IN_CHANNEL ; 
 unsigned int ALI_SPDIF_IN_SUPPORT ; 
 unsigned int inb (int /*<<< orphan*/ ) ; 
 unsigned int inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ali_enable_special_channel (struct snd_ali*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_ali_enable_spdif_in(struct snd_ali *codec)
{	
	unsigned int dwVal;

	dwVal = inl(ALI_REG(codec, ALI_GLOBAL_CONTROL));
	dwVal |= ALI_SPDIF_IN_SUPPORT;
	outl(dwVal, ALI_REG(codec, ALI_GLOBAL_CONTROL));

	dwVal = inb(ALI_REG(codec, ALI_SPDIF_CTRL));
	dwVal |= 0x02;
	outb(dwVal, ALI_REG(codec, ALI_SPDIF_CTRL));

	snd_ali_enable_special_channel(codec, ALI_SPDIF_IN_CHANNEL);
}