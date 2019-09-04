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
 int __bpf_fill_ja (struct bpf_test*,int,int) ; 

__attribute__((used)) static int bpf_fill_ja(struct bpf_test *self)
{
	/* Hits exactly 11 passes on x86_64 JIT. */
	return __bpf_fill_ja(self, 12, 9);
}