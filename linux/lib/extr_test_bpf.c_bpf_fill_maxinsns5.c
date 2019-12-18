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
struct sock_filter {int dummy; } ;
struct TYPE_3__ {unsigned int len; struct sock_filter* insns; } ;
struct TYPE_4__ {TYPE_1__ ptr; } ;
struct bpf_test {TYPE_2__ u; } ;

/* Variables and functions */
 int BPF_JA ; 
 int BPF_JMP ; 
 int BPF_K ; 
 unsigned int BPF_MAXINSNS ; 
 int BPF_RET ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct sock_filter __BPF_JUMP (int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sock_filter __BPF_STMT (int,int) ; 
 struct sock_filter* kmalloc_array (unsigned int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bpf_fill_maxinsns5(struct bpf_test *self)
{
	unsigned int len = BPF_MAXINSNS;
	struct sock_filter *insn;
	int i;

	insn = kmalloc_array(len, sizeof(*insn), GFP_KERNEL);
	if (!insn)
		return -ENOMEM;

	insn[0] = __BPF_JUMP(BPF_JMP | BPF_JA, len - 2, 0, 0);

	for (i = 1; i < len - 1; i++)
		insn[i] = __BPF_STMT(BPF_RET | BPF_K, 0xfefefefe);

	insn[len - 1] = __BPF_STMT(BPF_RET | BPF_K, 0xabababab);

	self->u.ptr.insns = insn;
	self->u.ptr.len = len;

	return 0;
}