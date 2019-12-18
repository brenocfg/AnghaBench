#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct bpf_prog {int dummy; } ;
typedef  int __u8 ;
struct TYPE_2__ {int aux; } ;

/* Variables and functions */
#define  CLASSIC 129 
#define  INTERNAL 128 
 int TEST_TYPE_MASK ; 
 int /*<<< orphan*/  bpf_prog_destroy (struct bpf_prog*) ; 
 int /*<<< orphan*/  bpf_prog_free (struct bpf_prog*) ; 
 TYPE_1__* tests ; 

__attribute__((used)) static void release_filter(struct bpf_prog *fp, int which)
{
	__u8 test_type = tests[which].aux & TEST_TYPE_MASK;

	switch (test_type) {
	case CLASSIC:
		bpf_prog_destroy(fp);
		break;
	case INTERNAL:
		bpf_prog_free(fp);
		break;
	}
}