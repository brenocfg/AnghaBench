#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int addr; int /*<<< orphan*/  area; } ;
struct esm_memory {TYPE_1__ buf; } ;
struct TYPE_5__ {int addr; } ;
struct es1968 {int clock; int in_measurement; int measure_apu; int measure_count; TYPE_3__* card; int /*<<< orphan*/  reg_lock; scalar_t__ io_port; TYPE_2__ dma; } ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CLOCK_MEASURE_BUFSIZE ; 
 int /*<<< orphan*/  ESM_APU_16BITLINEAR ; 
 int /*<<< orphan*/  ESM_APU_PCM_PLAY ; 
 int /*<<< orphan*/  ESM_BOB_FREQ ; 
 int ESM_HIRQ_DSIE ; 
 scalar_t__ ESM_PORT_HOST_IRQ ; 
 unsigned int __apu_get_register (struct es1968*,int,int) ; 
 int /*<<< orphan*/  __apu_set_register (struct es1968*,int,int,unsigned int) ; 
 int /*<<< orphan*/  apu_set_register (struct es1968*,int,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int inw (scalar_t__) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int ktime_to_us (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 int snd_es1968_alloc_apu_pair (struct es1968*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_es1968_apu_set_freq (struct es1968*,int,unsigned int) ; 
 int /*<<< orphan*/  snd_es1968_bob_dec (struct es1968*) ; 
 int /*<<< orphan*/  snd_es1968_bob_inc (struct es1968*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_es1968_free_apu_pair (struct es1968*,int) ; 
 int /*<<< orphan*/  snd_es1968_free_memory (struct es1968*,struct esm_memory*) ; 
 struct esm_memory* snd_es1968_new_memory (struct es1968*,int) ; 
 int /*<<< orphan*/  snd_es1968_trigger_apu (struct es1968*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wave_set_register (struct es1968*,int,int) ; 

__attribute__((used)) static void es1968_measure_clock(struct es1968 *chip)
{
	int i, apu;
	unsigned int pa, offset, t;
	struct esm_memory *memory;
	ktime_t start_time, stop_time;
	ktime_t diff;

	if (chip->clock == 0)
		chip->clock = 48000; /* default clock value */

	/* search 2 APUs (although one apu is enough) */
	if ((apu = snd_es1968_alloc_apu_pair(chip, ESM_APU_PCM_PLAY)) < 0) {
		dev_err(chip->card->dev, "Hmm, cannot find empty APU pair!?\n");
		return;
	}
	if ((memory = snd_es1968_new_memory(chip, CLOCK_MEASURE_BUFSIZE)) == NULL) {
		dev_warn(chip->card->dev,
			 "cannot allocate dma buffer - using default clock %d\n",
			 chip->clock);
		snd_es1968_free_apu_pair(chip, apu);
		return;
	}

	memset(memory->buf.area, 0, CLOCK_MEASURE_BUFSIZE);

	wave_set_register(chip, apu << 3, (memory->buf.addr - 0x10) & 0xfff8);

	pa = (unsigned int)((memory->buf.addr - chip->dma.addr) >> 1);
	pa |= 0x00400000;	/* System RAM (Bit 22) */

	/* initialize apu */
	for (i = 0; i < 16; i++)
		apu_set_register(chip, apu, i, 0x0000);

	apu_set_register(chip, apu, 0, 0x400f);
	apu_set_register(chip, apu, 4, ((pa >> 16) & 0xff) << 8);
	apu_set_register(chip, apu, 5, pa & 0xffff);
	apu_set_register(chip, apu, 6, (pa + CLOCK_MEASURE_BUFSIZE/2) & 0xffff);
	apu_set_register(chip, apu, 7, CLOCK_MEASURE_BUFSIZE/2);
	apu_set_register(chip, apu, 8, 0x0000);
	apu_set_register(chip, apu, 9, 0xD000);
	apu_set_register(chip, apu, 10, 0x8F08);
	apu_set_register(chip, apu, 11, 0x0000);
	spin_lock_irq(&chip->reg_lock);
	outw(1, chip->io_port + 0x04); /* clear WP interrupts */
	outw(inw(chip->io_port + ESM_PORT_HOST_IRQ) | ESM_HIRQ_DSIE, chip->io_port + ESM_PORT_HOST_IRQ); /* enable WP ints */
	spin_unlock_irq(&chip->reg_lock);

	snd_es1968_apu_set_freq(chip, apu, ((unsigned int)48000 << 16) / chip->clock); /* 48000 Hz */

	chip->in_measurement = 1;
	chip->measure_apu = apu;
	spin_lock_irq(&chip->reg_lock);
	snd_es1968_bob_inc(chip, ESM_BOB_FREQ);
	__apu_set_register(chip, apu, 5, pa & 0xffff);
	snd_es1968_trigger_apu(chip, apu, ESM_APU_16BITLINEAR);
	start_time = ktime_get();
	spin_unlock_irq(&chip->reg_lock);
	msleep(50);
	spin_lock_irq(&chip->reg_lock);
	offset = __apu_get_register(chip, apu, 5);
	stop_time = ktime_get();
	snd_es1968_trigger_apu(chip, apu, 0); /* stop */
	snd_es1968_bob_dec(chip);
	chip->in_measurement = 0;
	spin_unlock_irq(&chip->reg_lock);

	/* check the current position */
	offset -= (pa & 0xffff);
	offset &= 0xfffe;
	offset += chip->measure_count * (CLOCK_MEASURE_BUFSIZE/2);

	diff = ktime_sub(stop_time, start_time);
	t = ktime_to_us(diff);
	if (t == 0) {
		dev_err(chip->card->dev, "?? calculation error..\n");
	} else {
		offset *= 1000;
		offset = (offset / t) * 1000 + ((offset % t) * 1000) / t;
		if (offset < 47500 || offset > 48500) {
			if (offset >= 40000 && offset <= 50000)
				chip->clock = (chip->clock * offset) / 48000;
		}
		dev_info(chip->card->dev, "clocking to %d\n", chip->clock);
	}
	snd_es1968_free_memory(chip, memory);
	snd_es1968_free_apu_pair(chip, apu);
}