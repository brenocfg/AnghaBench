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
struct cfg {int dummy; } ;
struct bpf_insn {int dummy; } ;
typedef  int /*<<< orphan*/  cfg ;

/* Variables and functions */
 scalar_t__ cfg_build (struct cfg*,struct bpf_insn*,unsigned int) ; 
 int /*<<< orphan*/  cfg_destroy (struct cfg*) ; 
 int /*<<< orphan*/  cfg_dump (struct cfg*) ; 
 int /*<<< orphan*/  memset (struct cfg*,int /*<<< orphan*/ ,int) ; 

void dump_xlated_cfg(void *buf, unsigned int len)
{
	struct bpf_insn *insn = buf;
	struct cfg cfg;

	memset(&cfg, 0, sizeof(cfg));
	if (cfg_build(&cfg, insn, len))
		return;

	cfg_dump(&cfg);

	cfg_destroy(&cfg);
}