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
struct bpf_prog {int /*<<< orphan*/  expected_attach_type; } ;
struct bpf_insn_access_aux {int dummy; } ;
typedef  enum bpf_access_type { ____Placeholder_bpf_access_type } bpf_access_type ;

/* Variables and functions */
 int __sock_filter_check_attach_type (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_sock_is_valid_access (int,int,int,struct bpf_insn_access_aux*) ; 

__attribute__((used)) static bool sock_filter_is_valid_access(int off, int size,
					enum bpf_access_type type,
					const struct bpf_prog *prog,
					struct bpf_insn_access_aux *info)
{
	if (!bpf_sock_is_valid_access(off, size, type, info))
		return false;
	return __sock_filter_check_attach_type(off, type,
					       prog->expected_attach_type);
}