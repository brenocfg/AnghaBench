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
struct es1938 {scalar_t__ dma1_size; int /*<<< orphan*/  dma1_start; int /*<<< orphan*/  last_capture_dmaaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMAADDR ; 
 int /*<<< orphan*/  DMACLEAR ; 
 int /*<<< orphan*/  DMACOMMAND ; 
 int /*<<< orphan*/  DMACOUNT ; 
 int /*<<< orphan*/  DMAMASK ; 
 int /*<<< orphan*/  DMAMODE ; 
 int /*<<< orphan*/  SLDM_REG (struct es1938*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outw (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_es1938_capture_setdma(struct es1938 *chip)
{
	/* Enable DMA controller */
	outb(0xc4, SLDM_REG(chip, DMACOMMAND));
	/* 1. Master reset */
	outb(0, SLDM_REG(chip, DMACLEAR));
	/* 2. Mask DMA */
	outb(1, SLDM_REG(chip, DMAMASK));
	outb(0x14, SLDM_REG(chip, DMAMODE));
	outl(chip->dma1_start, SLDM_REG(chip, DMAADDR));
	chip->last_capture_dmaaddr = chip->dma1_start;
	outw(chip->dma1_size - 1, SLDM_REG(chip, DMACOUNT));
	/* 3. Unmask DMA */
	outb(0, SLDM_REG(chip, DMAMASK));
}