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

/* Variables and functions */
 int bpf_object__pin_maps (struct bpf_object*,char const*) ; 
 int bpf_object__pin_programs (struct bpf_object*,char const*) ; 
 int /*<<< orphan*/  bpf_object__unpin_maps (struct bpf_object*,char const*) ; 

int bpf_object__pin(struct bpf_object *obj, const char *path)
{
	int err;

	err = bpf_object__pin_maps(obj, path);
	if (err)
		return err;

	err = bpf_object__pin_programs(obj, path);
	if (err) {
		bpf_object__unpin_maps(obj, path);
		return err;
	}

	return 0;
}