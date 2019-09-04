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
 int /*<<< orphan*/  ALI_GC_CIR ; 
 int /*<<< orphan*/  ALI_REG (struct snd_ali*,int /*<<< orphan*/ ) ; 
 unsigned int ENDLP_IE ; 
 unsigned int MIDLP_IE ; 
 unsigned int inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_ali_disable_address_interrupt(struct snd_ali *codec)
{
	unsigned int gc;

	gc  = inl(ALI_REG(codec, ALI_GC_CIR));
	gc &= ~ENDLP_IE;
	gc &= ~MIDLP_IE;
	outl(gc, ALI_REG(codec, ALI_GC_CIR));
}