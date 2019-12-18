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
struct vm_area_struct {int /*<<< orphan*/  vm_page_prot; } ;
struct snd_pcm_substream {int dummy; } ;
struct azx_pcm {struct azx* chip; } ;
struct azx {scalar_t__ uc_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  pgprot_writecombine (int /*<<< orphan*/ ) ; 
 struct azx_pcm* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static void pcm_mmap_prepare(struct snd_pcm_substream *substream,
			     struct vm_area_struct *area)
{
#ifdef CONFIG_X86
	struct azx_pcm *apcm = snd_pcm_substream_chip(substream);
	struct azx *chip = apcm->chip;
	if (chip->uc_buffer)
		area->vm_page_prot = pgprot_writecombine(area->vm_page_prot);
#endif
}