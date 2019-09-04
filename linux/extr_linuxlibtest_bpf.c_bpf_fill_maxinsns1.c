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
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int BPF_K ; 
 unsigned int BPF_MAXINSNS ; 
 int BPF_RET ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct sock_filter __BPF_STMT (int,int /*<<< orphan*/ ) ; 
 struct sock_filter* kmalloc_array (unsigned int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bpf_fill_maxinsns1(struct bpf_test *self)
{
	unsigned int len = BPF_MAXINSNS;
	struct sock_filter *insn;
	__u32 k = ~0;
	int i;

	insn = kmalloc_array(len, sizeof(*insn), GFP_KERNEL);
	if (!insn)
		return -ENOMEM;

	for (i = 0; i < len; i++, k--)
		insn[i] = __BPF_STMT(BPF_RET | BPF_K, k);

	self->u.ptr.insns = insn;
	self->u.ptr.len = len;

	return 0;
}