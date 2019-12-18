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
struct bpf_object_load_attr {struct bpf_object* obj; } ;
struct bpf_object {int dummy; } ;

/* Variables and functions */
 int bpf_object__load_xattr (struct bpf_object_load_attr*) ; 

int bpf_object__load(struct bpf_object *obj)
{
	struct bpf_object_load_attr attr = {
		.obj = obj,
	};

	return bpf_object__load_xattr(&attr);
}