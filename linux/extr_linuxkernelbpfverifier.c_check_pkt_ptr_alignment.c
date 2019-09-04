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
 int /*<<< orphan*/  verbose (struct bpf_verifier_env*,char*,int,char*,scalar_t__,int,int) ; 

__attribute__((used)) static int check_pkt_ptr_alignment(struct bpf_verifier_env *env,
				   const struct bpf_reg_state *reg,
				   int off, int size, bool strict)
{
	struct tnum reg_off;
	int ip_align;

	/* Byte size accesses are always allowed. */
	if (!strict || size == 1)
		return 0;

	/* For platforms that do not have a Kconfig enabling
	 * CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS the value of
	 * NET_IP_ALIGN is universally set to '2'.  And on platforms
	 * that do set CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS, we get
	 * to this code only in strict mode where we want to emulate
	 * the NET_IP_ALIGN==2 checking.  Therefore use an
	 * unconditional IP align value of '2'.
	 */
	ip_align = 2;

	reg_off = tnum_add(reg->var_off, tnum_const(ip_align + reg->off + off));
	if (!tnum_is_aligned(reg_off, size)) {
		char tn_buf[48];

		tnum_strn(tn_buf, sizeof(tn_buf), reg->var_off);
		verbose(env,
			"misaligned packet access off %d+%s+%d+%d size %d\n",
			ip_align, tn_buf, reg->off, off, size);
		return -EACCES;
	}

	return 0;
}