#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct snd_cs46xx {TYPE_1__* card; struct dsp_spos_instance* dsp_spos_instance; } ;
struct dsp_symbol_entry {int symbol_type; scalar_t__ deleted; int /*<<< orphan*/ * module; int /*<<< orphan*/  address; int /*<<< orphan*/  symbol_name; } ;
struct TYPE_4__ {int nsymbols; int highest_frag_index; struct dsp_symbol_entry* symbols; } ;
struct dsp_spos_instance {TYPE_2__ symbol_table; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DSP_MAX_SYMBOLS ; 
 int /*<<< orphan*/ * cs46xx_dsp_lookup_symbol (struct snd_cs46xx*,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int find_free_symbol_index (struct dsp_spos_instance*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct dsp_symbol_entry *
add_symbol (struct snd_cs46xx * chip, char * symbol_name, u32 address, int type)
{
	struct dsp_spos_instance * ins = chip->dsp_spos_instance;
	struct dsp_symbol_entry * symbol = NULL;
	int index;

	if (ins->symbol_table.nsymbols == (DSP_MAX_SYMBOLS - 1)) {
		dev_err(chip->card->dev, "dsp_spos: symbol table is full\n");
		return NULL;
	}
  
	if (cs46xx_dsp_lookup_symbol(chip,
				     symbol_name,
				     type) != NULL) {
		dev_err(chip->card->dev,
			"dsp_spos: symbol <%s> duplicated\n", symbol_name);
		return NULL;
	}

	index = find_free_symbol_index (ins);

	strcpy (ins->symbol_table.symbols[index].symbol_name, symbol_name);
	ins->symbol_table.symbols[index].address = address;
	ins->symbol_table.symbols[index].symbol_type = type;
	ins->symbol_table.symbols[index].module = NULL;
	ins->symbol_table.symbols[index].deleted = 0;
	symbol = (ins->symbol_table.symbols + index);

	if (index > ins->symbol_table.highest_frag_index) 
		ins->symbol_table.highest_frag_index = index;

	if (index == ins->symbol_table.nsymbols)
		ins->symbol_table.nsymbols++; /* no frag. in list */

	return symbol;
}