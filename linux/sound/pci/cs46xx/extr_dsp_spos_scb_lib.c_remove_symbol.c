#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_cs46xx {struct dsp_spos_instance* dsp_spos_instance; } ;
struct dsp_symbol_entry {int deleted; } ;
struct TYPE_2__ {int nsymbols; int highest_frag_index; struct dsp_symbol_entry* symbols; } ;
struct dsp_spos_instance {TYPE_1__ symbol_table; } ;

/* Variables and functions */
 scalar_t__ snd_BUG_ON (int) ; 

__attribute__((used)) static void remove_symbol (struct snd_cs46xx * chip, struct dsp_symbol_entry * symbol)
{
	struct dsp_spos_instance * ins = chip->dsp_spos_instance;
	int symbol_index = (int)(symbol - ins->symbol_table.symbols);

	if (snd_BUG_ON(ins->symbol_table.nsymbols <= 0))
		return;
	if (snd_BUG_ON(symbol_index < 0 ||
		       symbol_index >= ins->symbol_table.nsymbols))
		return;

	ins->symbol_table.symbols[symbol_index].deleted = 1;

	if (symbol_index < ins->symbol_table.highest_frag_index) {
		ins->symbol_table.highest_frag_index = symbol_index;
	}
  
	if (symbol_index == ins->symbol_table.nsymbols - 1)
		ins->symbol_table.nsymbols --;

	if (ins->symbol_table.highest_frag_index > ins->symbol_table.nsymbols) {
		ins->symbol_table.highest_frag_index = ins->symbol_table.nsymbols;
	}

}