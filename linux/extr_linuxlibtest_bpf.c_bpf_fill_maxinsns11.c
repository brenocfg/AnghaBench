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
struct bpf_test {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_MAXINSNS ; 
 int __bpf_fill_ja (struct bpf_test*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bpf_fill_maxinsns11(struct bpf_test *self)
{
	/* Hits 70 passes on x86_64, so cannot get JITed there. */
	return __bpf_fill_ja(self, BPF_MAXINSNS, 68);
}