#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct snd_cs46xx {TYPE_1__* card; struct dsp_spos_instance* dsp_spos_instance; } ;
struct TYPE_10__ {int nsymbols; size_t highest_frag_index; TYPE_4__* symbols; } ;
struct TYPE_8__ {int offset; } ;
struct dsp_spos_instance {TYPE_5__ symbol_table; TYPE_3__ code; } ;
struct TYPE_7__ {int nsymbols; TYPE_4__* symbols; } ;
struct dsp_module_desc {int overlay_begin_address; TYPE_2__ symbol_table; } ;
struct TYPE_9__ {int address; scalar_t__ deleted; struct dsp_module_desc* module; int /*<<< orphan*/  symbol_type; int /*<<< orphan*/  symbol_name; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DSP_MAX_SYMBOLS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  SYMBOL_CONSTANT ; 
 int /*<<< orphan*/ * cs46xx_dsp_lookup_symbol (struct snd_cs46xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int add_symbols (struct snd_cs46xx * chip, struct dsp_module_desc * module)
{
	int i;
	struct dsp_spos_instance * ins = chip->dsp_spos_instance;

	if (module->symbol_table.nsymbols > 0) {
		if (!strcmp(module->symbol_table.symbols[0].symbol_name, "OVERLAYBEGINADDRESS") &&
		    module->symbol_table.symbols[0].symbol_type == SYMBOL_CONSTANT ) {
			module->overlay_begin_address = module->symbol_table.symbols[0].address;
		}
	}

	for (i = 0;i < module->symbol_table.nsymbols; ++i) {
		if (ins->symbol_table.nsymbols == (DSP_MAX_SYMBOLS - 1)) {
			dev_err(chip->card->dev,
				"dsp_spos: symbol table is full\n");
			return -ENOMEM;
		}


		if (cs46xx_dsp_lookup_symbol(chip,
					     module->symbol_table.symbols[i].symbol_name,
					     module->symbol_table.symbols[i].symbol_type) == NULL) {

			ins->symbol_table.symbols[ins->symbol_table.nsymbols] = module->symbol_table.symbols[i];
			ins->symbol_table.symbols[ins->symbol_table.nsymbols].address += ((ins->code.offset / 2) - module->overlay_begin_address);
			ins->symbol_table.symbols[ins->symbol_table.nsymbols].module = module;
			ins->symbol_table.symbols[ins->symbol_table.nsymbols].deleted = 0;

			if (ins->symbol_table.nsymbols > ins->symbol_table.highest_frag_index) 
				ins->symbol_table.highest_frag_index = ins->symbol_table.nsymbols;

			ins->symbol_table.nsymbols++;
		} else {
#if 0
			dev_dbg(chip->card->dev,
				"dsp_spos: symbol <%s> duplicated, probably nothing wrong with that (Cirrus?)\n",
				module->symbol_table.symbols[i].symbol_name); */
#endif
		}
	}

	return 0;
}