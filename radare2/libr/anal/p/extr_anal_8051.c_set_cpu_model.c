#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut32 ;
struct TYPE_11__ {char* name; scalar_t__ map_pdata; scalar_t__ map_code; scalar_t__ map_xdata; scalar_t__ map_sfr; scalar_t__ map_idata; } ;
struct TYPE_9__ {scalar_t__ cmd; } ;
struct TYPE_8__ {scalar_t__ fd_get_name; } ;
struct TYPE_10__ {char* cpu; TYPE_2__ coreb; TYPE_1__ iob; int /*<<< orphan*/  reg; } ;
typedef  TYPE_3__ RAnal ;

/* Variables and functions */
 int /*<<< orphan*/  I8051_IDATA ; 
 int /*<<< orphan*/  I8051_SFR ; 
 int /*<<< orphan*/  I8051_XDATA ; 
 TYPE_6__* cpu_curr_model ; 
 TYPE_6__* cpu_models ; 
 scalar_t__ i8051_reg_read (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  i8051_reg_write (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  map_cpu_memory (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 scalar_t__ r_str_casecmp (char const*,char*) ; 

__attribute__((used)) static void set_cpu_model(RAnal *anal, bool force) {
	ut32 addr_idata, addr_sfr, addr_xdata;

	if (!anal->reg) {
		return;
	}

	const char *cpu = anal->cpu;
	if (!cpu || !cpu[0]) {
		cpu = cpu_models[0].name;
	}

	// if cpu model changed, reinitialize emulation
	if (force || !cpu_curr_model || r_str_casecmp (cpu, cpu_curr_model->name)) {
		// find model by name
		int i = 0;
		while (cpu_models[i].name && r_str_casecmp (cpu, cpu_models[i].name)) {
			i++;
		}
		if (!cpu_models[i].name) {
			i = 0;	// if not found, default to generic 8051
		}
		cpu_curr_model = &cpu_models[i];

		// TODO: Add flags as needed - seek using pseudo registers works w/o flags

		// set memory map registers
		addr_idata = cpu_models[i].map_idata;
		addr_sfr = cpu_models[i].map_sfr;
		addr_xdata = cpu_models[i].map_xdata;
		i8051_reg_write (anal->reg, "_code", cpu_models[i].map_code);
		i8051_reg_write (anal->reg, "_idata", addr_idata);
		i8051_reg_write (anal->reg, "_sfr", addr_sfr - 0x80);
		i8051_reg_write (anal->reg, "_xdata", addr_xdata);
		i8051_reg_write (anal->reg, "_pdata", cpu_models[i].map_pdata);
	} else {
		addr_idata = i8051_reg_read (anal->reg, "_idata");
		addr_sfr = i8051_reg_read (anal->reg, "_sfr") + 0x80;
		addr_xdata = i8051_reg_read (anal->reg, "_xdata");
	}

	// (Re)allocate memory as needed.
	// We assume that code is allocated with firmware image
	if (anal->iob.fd_get_name && anal->coreb.cmd) {
		map_cpu_memory (anal, I8051_IDATA, addr_idata, 0x100, force);
		map_cpu_memory (anal, I8051_SFR, addr_sfr, 0x80, force);
		map_cpu_memory (anal, I8051_XDATA, addr_xdata, 0x10000, force);
	}
}