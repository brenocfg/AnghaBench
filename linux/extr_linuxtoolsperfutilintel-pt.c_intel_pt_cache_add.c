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
typedef  void* u64 ;
struct machine {int dummy; } ;
struct intel_pt_insn {int /*<<< orphan*/  buf; int /*<<< orphan*/  rel; int /*<<< orphan*/  length; int /*<<< orphan*/  branch; int /*<<< orphan*/  op; } ;
struct intel_pt_cache_entry {int /*<<< orphan*/  entry; int /*<<< orphan*/  insn; int /*<<< orphan*/  rel; int /*<<< orphan*/  length; int /*<<< orphan*/  branch; int /*<<< orphan*/  op; void* byte_cnt; void* insn_cnt; } ;
struct dso {int dummy; } ;
struct auxtrace_cache {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INTEL_PT_INSN_BUF_SZ ; 
 int auxtrace_cache__add (struct auxtrace_cache*,void*,int /*<<< orphan*/ *) ; 
 struct intel_pt_cache_entry* auxtrace_cache__alloc_entry (struct auxtrace_cache*) ; 
 int /*<<< orphan*/  auxtrace_cache__free_entry (struct auxtrace_cache*,struct intel_pt_cache_entry*) ; 
 struct auxtrace_cache* intel_pt_cache (struct dso*,struct machine*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int intel_pt_cache_add(struct dso *dso, struct machine *machine,
			      u64 offset, u64 insn_cnt, u64 byte_cnt,
			      struct intel_pt_insn *intel_pt_insn)
{
	struct auxtrace_cache *c = intel_pt_cache(dso, machine);
	struct intel_pt_cache_entry *e;
	int err;

	if (!c)
		return -ENOMEM;

	e = auxtrace_cache__alloc_entry(c);
	if (!e)
		return -ENOMEM;

	e->insn_cnt = insn_cnt;
	e->byte_cnt = byte_cnt;
	e->op = intel_pt_insn->op;
	e->branch = intel_pt_insn->branch;
	e->length = intel_pt_insn->length;
	e->rel = intel_pt_insn->rel;
	memcpy(e->insn, intel_pt_insn->buf, INTEL_PT_INSN_BUF_SZ);

	err = auxtrace_cache__add(c, offset, &e->entry);
	if (err)
		auxtrace_cache__free_entry(c, e);

	return err;
}