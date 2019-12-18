#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  max; int /*<<< orphan*/  mem_addr; scalar_t__ curlen; } ;
struct TYPE_11__ {int mem_addr; int /*<<< orphan*/  max; scalar_t__ curlen; } ;
struct TYPE_10__ {int /*<<< orphan*/  max; int /*<<< orphan*/  mem_addr; scalar_t__ curlen; } ;
struct TYPE_9__ {int /*<<< orphan*/  max; int /*<<< orphan*/  mem_addr; scalar_t__ curlen; } ;
struct snd_m3 {TYPE_6__ msrc_list; TYPE_5__ dma_list; TYPE_4__ adc1_list; TYPE_3__ mixer_list; TYPE_2__* assp_minisrc_image; TYPE_1__* assp_kernel_image; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_8__ {unsigned int size; scalar_t__ data; } ;
struct TYPE_7__ {unsigned int size; scalar_t__ data; } ;

/* Variables and functions */
 int ARB_VOLUME ; 
 int /*<<< orphan*/  KDATA_ADC1_XFER0 ; 
 int KDATA_BASE_ADDR ; 
 int KDATA_BASE_ADDR2 ; 
 int KDATA_CURRENT_DMA ; 
 int KDATA_DAC_LEFT_VOLUME ; 
 int KDATA_DAC_RIGHT_VOLUME ; 
 int KDATA_DMA_XFER0 ; 
 int /*<<< orphan*/  KDATA_INSTANCE0_MINISRC ; 
 int KDATA_MIXER_TASK_NUMBER ; 
 int /*<<< orphan*/  KDATA_MIXER_XFER0 ; 
 int KDATA_TASK0 ; 
 int /*<<< orphan*/  MAX_INSTANCE_MINISRC ; 
 int /*<<< orphan*/  MAX_VIRTUAL_ADC1_CHANNELS ; 
 int /*<<< orphan*/  MAX_VIRTUAL_DMA_CHANNELS ; 
 int /*<<< orphan*/  MAX_VIRTUAL_MIXER_CHANNELS ; 
 int /*<<< orphan*/  MEMTYPE_INTERNAL_CODE ; 
 int /*<<< orphan*/  MEMTYPE_INTERNAL_DATA ; 
 int MINISRC_COEF_LOC ; 
 unsigned int MINISRC_LPF_LEN ; 
 int NUM_UNITS_KERNEL_DATA ; 
 int REV_B_CODE_MEMORY_BEGIN ; 
 int REV_B_DATA_MEMORY_UNIT_LENGTH ; 
 int le16_to_cpu (int /*<<< orphan*/  const) ; 
 int* minisrc_lpf ; 
 int /*<<< orphan*/  snd_m3_assp_write (struct snd_m3*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void snd_m3_assp_init(struct snd_m3 *chip)
{
	unsigned int i;
	const __le16 *data;

	/* zero kernel data */
	for (i = 0; i < (REV_B_DATA_MEMORY_UNIT_LENGTH * NUM_UNITS_KERNEL_DATA) / 2; i++)
		snd_m3_assp_write(chip, MEMTYPE_INTERNAL_DATA, 
				  KDATA_BASE_ADDR + i, 0);

	/* zero mixer data? */
	for (i = 0; i < (REV_B_DATA_MEMORY_UNIT_LENGTH * NUM_UNITS_KERNEL_DATA) / 2; i++)
		snd_m3_assp_write(chip, MEMTYPE_INTERNAL_DATA,
				  KDATA_BASE_ADDR2 + i, 0);

	/* init dma pointer */
	snd_m3_assp_write(chip, MEMTYPE_INTERNAL_DATA,
			  KDATA_CURRENT_DMA,
			  KDATA_DMA_XFER0);

	/* write kernel into code memory.. */
	data = (const __le16 *)chip->assp_kernel_image->data;
	for (i = 0 ; i * 2 < chip->assp_kernel_image->size; i++) {
		snd_m3_assp_write(chip, MEMTYPE_INTERNAL_CODE, 
				  REV_B_CODE_MEMORY_BEGIN + i,
				  le16_to_cpu(data[i]));
	}

	/*
	 * We only have this one client and we know that 0x400
	 * is free in our kernel's mem map, so lets just
	 * drop it there.  It seems that the minisrc doesn't
	 * need vectors, so we won't bother with them..
	 */
	data = (const __le16 *)chip->assp_minisrc_image->data;
	for (i = 0; i * 2 < chip->assp_minisrc_image->size; i++) {
		snd_m3_assp_write(chip, MEMTYPE_INTERNAL_CODE, 
				  0x400 + i, le16_to_cpu(data[i]));
	}

	/*
	 * write the coefficients for the low pass filter?
	 */
	for (i = 0; i < MINISRC_LPF_LEN ; i++) {
		snd_m3_assp_write(chip, MEMTYPE_INTERNAL_CODE,
				  0x400 + MINISRC_COEF_LOC + i,
				  minisrc_lpf[i]);
	}

	snd_m3_assp_write(chip, MEMTYPE_INTERNAL_CODE,
			  0x400 + MINISRC_COEF_LOC + MINISRC_LPF_LEN,
			  0x8000);

	/*
	 * the minisrc is the only thing on
	 * our task list..
	 */
	snd_m3_assp_write(chip, MEMTYPE_INTERNAL_DATA, 
			  KDATA_TASK0,
			  0x400);

	/*
	 * init the mixer number..
	 */

	snd_m3_assp_write(chip, MEMTYPE_INTERNAL_DATA,
			  KDATA_MIXER_TASK_NUMBER,0);

	/*
	 * EXTREME KERNEL MASTER VOLUME
	 */
	snd_m3_assp_write(chip, MEMTYPE_INTERNAL_DATA,
			  KDATA_DAC_LEFT_VOLUME, ARB_VOLUME);
	snd_m3_assp_write(chip, MEMTYPE_INTERNAL_DATA,
			  KDATA_DAC_RIGHT_VOLUME, ARB_VOLUME);

	chip->mixer_list.curlen = 0;
	chip->mixer_list.mem_addr = KDATA_MIXER_XFER0;
	chip->mixer_list.max = MAX_VIRTUAL_MIXER_CHANNELS;
	chip->adc1_list.curlen = 0;
	chip->adc1_list.mem_addr = KDATA_ADC1_XFER0;
	chip->adc1_list.max = MAX_VIRTUAL_ADC1_CHANNELS;
	chip->dma_list.curlen = 0;
	chip->dma_list.mem_addr = KDATA_DMA_XFER0;
	chip->dma_list.max = MAX_VIRTUAL_DMA_CHANNELS;
	chip->msrc_list.curlen = 0;
	chip->msrc_list.mem_addr = KDATA_INSTANCE0_MINISRC;
	chip->msrc_list.max = MAX_INSTANCE_MINISRC;
}