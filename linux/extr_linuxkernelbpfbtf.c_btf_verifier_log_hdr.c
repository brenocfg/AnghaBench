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
typedef  int /*<<< orphan*/  u32 ;
struct bpf_verifier_log {int dummy; } ;
struct btf_verifier_env {struct btf* btf; struct bpf_verifier_log log; } ;
struct btf_header {int /*<<< orphan*/  str_len; int /*<<< orphan*/  str_off; int /*<<< orphan*/  type_len; int /*<<< orphan*/  type_off; int /*<<< orphan*/  hdr_len; int /*<<< orphan*/  flags; int /*<<< orphan*/  version; int /*<<< orphan*/  magic; } ;
struct btf {struct btf_header hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  __btf_verifier_log (struct bpf_verifier_log*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_verifier_log_needed (struct bpf_verifier_log*) ; 

__attribute__((used)) static void btf_verifier_log_hdr(struct btf_verifier_env *env,
				 u32 btf_data_size)
{
	struct bpf_verifier_log *log = &env->log;
	const struct btf *btf = env->btf;
	const struct btf_header *hdr;

	if (!bpf_verifier_log_needed(log))
		return;

	hdr = &btf->hdr;
	__btf_verifier_log(log, "magic: 0x%x\n", hdr->magic);
	__btf_verifier_log(log, "version: %u\n", hdr->version);
	__btf_verifier_log(log, "flags: 0x%x\n", hdr->flags);
	__btf_verifier_log(log, "hdr_len: %u\n", hdr->hdr_len);
	__btf_verifier_log(log, "type_off: %u\n", hdr->type_off);
	__btf_verifier_log(log, "type_len: %u\n", hdr->type_len);
	__btf_verifier_log(log, "str_off: %u\n", hdr->str_off);
	__btf_verifier_log(log, "str_len: %u\n", hdr->str_len);
	__btf_verifier_log(log, "btf_total_size: %u\n", btf_data_size);
}