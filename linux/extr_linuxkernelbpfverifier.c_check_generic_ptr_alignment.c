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
typedef  int /*<<< orphan*/  tn_buf ;
struct tnum {int dummy; } ;
struct bpf_verifier_env {int dummy; } ;
struct bpf_reg_state {scalar_t__ off; int /*<<< orphan*/  var_off; } ;

/* Variables and functions */
 int EACCES ; 
 struct tnum tnum_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tnum_const (scalar_t__) ; 
 int /*<<< orphan*/  tnum_is_aligned (struct tnum,int) ; 
 int /*<<< orphan*/  tnum_strn (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbose (struct bpf_verifier_env*,char*,char const*,char*,scalar_t__,int,int) ; 

__attribute__((used)) static int check_generic_ptr_alignment(struct bpf_verifier_env *env,
				       const struct bpf_reg_state *reg,
				       const char *pointer_desc,
				       int off, int size, bool strict)
{
	struct tnum reg_off;

	/* Byte size accesses are always allowed. */
	if (!strict || size == 1)
		return 0;

	reg_off = tnum_add(reg->var_off, tnum_const(reg->off + off));
	if (!tnum_is_aligned(reg_off, size)) {
		char tn_buf[48];

		tnum_strn(tn_buf, sizeof(tn_buf), reg->var_off);
		verbose(env, "misaligned %saccess off %s+%d+%d size %d\n",
			pointer_desc, tn_buf, reg->off, off, size);
		return -EACCES;
	}

	return 0;
}