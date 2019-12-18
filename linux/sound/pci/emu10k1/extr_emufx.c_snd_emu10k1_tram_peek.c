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
typedef  int u32 ;
struct snd_emu10k1_fx8010_code {int /*<<< orphan*/ * tram_addr_map; int /*<<< orphan*/ * tram_data_map; int /*<<< orphan*/  tram_valid; } ;
struct snd_emu10k1 {scalar_t__ audigy; } ;

/* Variables and functions */
 scalar_t__ A_TANKMEMCTLREGBASE ; 
 int EFAULT ; 
 scalar_t__ TANKMEMADDRREGBASE ; 
 scalar_t__ TANKMEMDATAREGBASE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ put_user (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 int snd_emu10k1_ptr_read (struct snd_emu10k1*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_emu10k1_tram_peek(struct snd_emu10k1 *emu,
				 struct snd_emu10k1_fx8010_code *icode)
{
	int tram;
	u32 val, addr;

	memset(icode->tram_valid, 0, sizeof(icode->tram_valid));
	for (tram = 0; tram < (emu->audigy ? 0x100 : 0xa0); tram++) {
		set_bit(tram, icode->tram_valid);
		val = snd_emu10k1_ptr_read(emu, TANKMEMDATAREGBASE + tram, 0);
		if (!emu->audigy) {
			addr = snd_emu10k1_ptr_read(emu, TANKMEMADDRREGBASE + tram, 0);
		} else {
			addr = snd_emu10k1_ptr_read(emu, TANKMEMADDRREGBASE + tram, 0) >> 12;
			addr |= snd_emu10k1_ptr_read(emu, A_TANKMEMCTLREGBASE + tram, 0) << 20;
		}
		if (put_user(val, &icode->tram_data_map[tram]) ||
		    put_user(addr, &icode->tram_addr_map[tram]))
			return -EFAULT;
	}
	return 0;
}