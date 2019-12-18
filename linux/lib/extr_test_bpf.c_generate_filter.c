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
struct sock_fprog_kern {unsigned int len; void* filter; } ;
struct bpf_prog {unsigned int len; TYPE_1__* aux; int /*<<< orphan*/  insnsi; int /*<<< orphan*/  type; } ;
struct bpf_insn {int dummy; } ;
typedef  int __u8 ;
struct TYPE_4__ {int aux; int expected_errcode; int /*<<< orphan*/  stack_depth; } ;
struct TYPE_3__ {int /*<<< orphan*/  stack_depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_PROG_TYPE_SOCKET_FILTER ; 
#define  CLASSIC 129 
 int EINVAL ; 
 int ENOMEM ; 
 int FLAG_EXPECTED_FAIL ; 
#define  INTERNAL 128 
 int TEST_TYPE_MASK ; 
 struct bpf_prog* bpf_prog_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bpf_prog_create (struct bpf_prog**,struct sock_fprog_kern*) ; 
 struct bpf_prog* bpf_prog_select_runtime (struct bpf_prog*,int*) ; 
 int /*<<< orphan*/  bpf_prog_size (unsigned int) ; 
 unsigned int filter_length (int) ; 
 void* filter_pointer (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 
 TYPE_2__* tests ; 

__attribute__((used)) static struct bpf_prog *generate_filter(int which, int *err)
{
	__u8 test_type = tests[which].aux & TEST_TYPE_MASK;
	unsigned int flen = filter_length(which);
	void *fptr = filter_pointer(which);
	struct sock_fprog_kern fprog;
	struct bpf_prog *fp;

	switch (test_type) {
	case CLASSIC:
		fprog.filter = fptr;
		fprog.len = flen;

		*err = bpf_prog_create(&fp, &fprog);
		if (tests[which].aux & FLAG_EXPECTED_FAIL) {
			if (*err == tests[which].expected_errcode) {
				pr_cont("PASS\n");
				/* Verifier rejected filter as expected. */
				*err = 0;
				return NULL;
			} else {
				pr_cont("UNEXPECTED_PASS\n");
				/* Verifier didn't reject the test that's
				 * bad enough, just return!
				 */
				*err = -EINVAL;
				return NULL;
			}
		}
		if (*err) {
			pr_cont("FAIL to prog_create err=%d len=%d\n",
				*err, fprog.len);
			return NULL;
		}
		break;

	case INTERNAL:
		fp = bpf_prog_alloc(bpf_prog_size(flen), 0);
		if (fp == NULL) {
			pr_cont("UNEXPECTED_FAIL no memory left\n");
			*err = -ENOMEM;
			return NULL;
		}

		fp->len = flen;
		/* Type doesn't really matter here as long as it's not unspec. */
		fp->type = BPF_PROG_TYPE_SOCKET_FILTER;
		memcpy(fp->insnsi, fptr, fp->len * sizeof(struct bpf_insn));
		fp->aux->stack_depth = tests[which].stack_depth;

		/* We cannot error here as we don't need type compatibility
		 * checks.
		 */
		fp = bpf_prog_select_runtime(fp, err);
		if (*err) {
			pr_cont("FAIL to select_runtime err=%d\n", *err);
			return NULL;
		}
		break;
	}

	*err = 0;
	return fp;
}