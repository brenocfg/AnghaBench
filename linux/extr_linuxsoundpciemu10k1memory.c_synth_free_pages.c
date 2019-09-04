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
struct snd_emu10k1_memblk {int dummy; } ;
struct snd_emu10k1 {int /*<<< orphan*/  memhdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  __synth_free_pages (struct snd_emu10k1*,int,int) ; 
 int /*<<< orphan*/  get_single_page_range (int /*<<< orphan*/ ,struct snd_emu10k1_memblk*,int*,int*) ; 

__attribute__((used)) static int synth_free_pages(struct snd_emu10k1 *emu, struct snd_emu10k1_memblk *blk)
{
	int first_page, last_page;

	get_single_page_range(emu->memhdr, blk, &first_page, &last_page);
	__synth_free_pages(emu, first_page, last_page);
	return 0;
}