#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_16__ ;
typedef  struct TYPE_18__   TYPE_13__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  asmparser ;
struct TYPE_23__ {char* value; } ;
struct TYPE_22__ {TYPE_16__* anal; int /*<<< orphan*/  config; TYPE_13__* assembler; TYPE_2__* print; int /*<<< orphan*/  bin; int /*<<< orphan*/  dbg; int /*<<< orphan*/  egg; } ;
struct TYPE_21__ {int big_endian; } ;
struct TYPE_20__ {char* cpus; int bits; } ;
struct TYPE_19__ {int bits; int /*<<< orphan*/  sdb_types; int /*<<< orphan*/  syscall; } ;
struct TYPE_18__ {int /*<<< orphan*/  bits; TYPE_1__* cur; } ;
typedef  TYPE_3__ RCore ;
typedef  TYPE_4__ RConfigNode ;

/* Variables and functions */
 int /*<<< orphan*/  R_ANAL_ARCHINFO_ALIGN ; 
 int R_SYS_BITS ; 
 int /*<<< orphan*/  R_SYS_OS ; 
 int /*<<< orphan*/  __setsegoff (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eprintf (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  print_node_options (TYPE_4__*) ; 
 int r_anal_archinfo (TYPE_16__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_asm_set_big_endian (TYPE_13__*,int) ; 
 int /*<<< orphan*/  r_asm_set_cpu (TYPE_13__*,char*) ; 
 int /*<<< orphan*/  r_asm_use (TYPE_13__*,char*) ; 
 int r_bin_is_big_endian (int /*<<< orphan*/ ) ; 
 char const* r_config_get (int /*<<< orphan*/ ,char*) ; 
 int r_config_get_i (int /*<<< orphan*/ ,char*) ; 
 TYPE_4__* r_config_node_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_config_set (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  r_config_set_i (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  r_core_anal_cc_init (TYPE_3__*) ; 
 int /*<<< orphan*/  r_core_anal_type_init (TYPE_3__*) ; 
 int /*<<< orphan*/  r_debug_set_arch (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  r_egg_setup (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_syscall_setup (int /*<<< orphan*/ ,char const*,int,char const*,char const*) ; 
 int /*<<< orphan*/  rasm2_list (TYPE_3__*,int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 char* strchr (char*,char) ; 
 char* strdup (char const*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strstr (char*,char*) ; 
 int /*<<< orphan*/  update_asmarch_options (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  update_asmcpu_options (TYPE_3__*,TYPE_4__*) ; 

__attribute__((used)) static bool cb_asmarch(void *user, void *data) {
	char asmparser[32];
	RCore *core = (RCore *) user;
	RConfigNode *node = (RConfigNode *) data;
	const char *asmos = NULL;
	int bits = R_SYS_BITS;
	if (!*node->value || !core || !core->assembler) {
		return false;
	}
	asmos = r_config_get (core->config, "asm.os");
	if (core && core->anal && core->anal->bits) {
		bits = core->anal->bits;
	}
	if (node->value[0] == '?') {
		update_asmarch_options (core, node);
		if (strlen (node->value) > 1 && node->value[1] == '?') {
			/* print more verbose help instead of plain option values */
			rasm2_list (core, NULL, node->value[1]);
			return false;
		} else {
			print_node_options (node);
			return false;
		}
	}
	r_egg_setup (core->egg, node->value, bits, 0, R_SYS_OS);

	if (!r_asm_use (core->assembler, node->value)) {
		eprintf ("asm.arch: cannot find (%s)\n", node->value);
		return false;
	}
	//we should strdup here otherwise will crash if any r_config_set
	//free the old value
	char *asm_cpu = strdup (r_config_get (core->config, "asm.cpu"));
	if (core->assembler->cur) {
		const char *newAsmCPU = core->assembler->cur->cpus;
		if (newAsmCPU) {
			if (*newAsmCPU) {
				char *nac = strdup (newAsmCPU);
				char *comma = strchr (nac, ',');
				if (comma) {
					if (!*asm_cpu || (*asm_cpu && !strstr(nac, asm_cpu))) {
						*comma = 0;
						r_config_set (core->config, "asm.cpu", nac);
					}
				}
				free (nac);
			} else {
				r_config_set (core->config, "asm.cpu", "");
			}
		}
		bits = core->assembler->cur->bits;
		if (8 & bits) {
			bits = 8;
		} else if (16 & bits) {
			bits = 16;
		} else if (32 & bits) {
			bits = 32;
		} else {
			bits = 64;
		}
	}
	snprintf (asmparser, sizeof (asmparser), "%s.pseudo", node->value);
	r_config_set (core->config, "asm.parser", asmparser);
	if (core->assembler->cur && core->anal &&
	    !(core->assembler->cur->bits & core->anal->bits)) {
		r_config_set_i (core->config, "asm.bits", bits);
	}

	//r_debug_set_arch (core->dbg, r_sys_arch_id (node->value), bits);
	r_debug_set_arch (core->dbg, node->value, bits);
	if (!r_config_set (core->config, "anal.arch", node->value)) {
		char *p, *s = strdup (node->value);
		if (s) {
			p = strchr (s, '.');
			if (p) {
				*p = 0;
			}
			if (!r_config_set (core->config, "anal.arch", s)) {
				/* fall back to the anal.null plugin */
				r_config_set (core->config, "anal.arch", "null");
			}
			free (s);
		}
	}
	// set pcalign
	if (core->anal) {
		const char *asmcpu = r_config_get (core->config, "asm.cpu");
		if (!r_syscall_setup (core->anal->syscall, node->value, core->anal->bits, asmcpu, asmos)) {
			//eprintf ("asm.arch: Cannot setup syscall '%s/%s' from '%s'\n",
			//	node->value, asmos, R2_LIBDIR"/radare2/"R2_VERSION"/syscall");
		}
	}
	//if (!strcmp (node->value, "bf"))
	//	r_config_set (core->config, "dbg.backend", "bf");
	__setsegoff (core->config, node->value, core->assembler->bits);

	// set a default endianness
	int bigbin = r_bin_is_big_endian (core->bin);
	if (bigbin == -1 /* error: no endianness detected in binary */) {
		bigbin = r_config_get_i (core->config, "cfg.bigendian");
	}

	// try to set endian of RAsm to match binary
	r_asm_set_big_endian (core->assembler, bigbin);
	// set endian of display to match binary
	core->print->big_endian = bigbin;

	r_asm_set_cpu (core->assembler, asm_cpu);
	free (asm_cpu);
	RConfigNode *asmcpu = r_config_node_get (core->config, "asm.cpu");
	if (asmcpu) {
		update_asmcpu_options (core, asmcpu);
	}
	{
		int v = r_anal_archinfo (core->anal, R_ANAL_ARCHINFO_ALIGN);
		if (v != -1) {
			r_config_set_i (core->config, "asm.pcalign", v);
		} else {
			r_config_set_i (core->config, "asm.pcalign", 0);
		}
	}
	/* reload types and cc info */
	// changing asm.arch changes anal.arch
	// changing anal.arch sets types db
	// so ressetting is redundant and may lead to bugs
	// 1 case this is usefull is when sdb_types is null
	if (!core->anal || !core->anal->sdb_types) {
		r_core_anal_type_init (core);
	}
	r_core_anal_cc_init (core);
	return true;
}