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
struct bpf_test {int retval; int /*<<< orphan*/  prog_len; } ;

/* Variables and functions */
 void bpf_fill_scale1 (struct bpf_test*) ; 
 void bpf_fill_scale2 (struct bpf_test*) ; 

__attribute__((used)) static void bpf_fill_scale(struct bpf_test *self)
{
	switch (self->retval) {
	case 1:
		return bpf_fill_scale1(self);
	case 2:
		return bpf_fill_scale2(self);
	default:
		self->prog_len = 0;
		break;
	}
}