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
struct bpf_object {int dummy; } ;
typedef  int /*<<< orphan*/  bf ;

/* Variables and functions */
 int bpf_object__load (struct bpf_object*) ; 
 int /*<<< orphan*/  libbpf_strerror (int,char*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,char*) ; 

int bpf__load(struct bpf_object *obj)
{
	int err;

	err = bpf_object__load(obj);
	if (err) {
		char bf[128];
		libbpf_strerror(err, bf, sizeof(bf));
		pr_debug("bpf: load objects failed: err=%d: (%s)\n", err, bf);
		return err;
	}
	return 0;
}