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
struct es1938 {int /*<<< orphan*/  dma2_size; int /*<<< orphan*/  dma2_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO2DMAADDR ; 
 int /*<<< orphan*/  AUDIO2DMACOUNT ; 
 int /*<<< orphan*/  AUDIO2MODE ; 
 int /*<<< orphan*/  SLIO_REG (struct es1938*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_es1938_playback1_setdma(struct es1938 *chip)
{
	outb(0x00, SLIO_REG(chip, AUDIO2MODE));
	outl(chip->dma2_start, SLIO_REG(chip, AUDIO2DMAADDR));
	outw(0, SLIO_REG(chip, AUDIO2DMACOUNT));
	outw(chip->dma2_size, SLIO_REG(chip, AUDIO2DMACOUNT));
}