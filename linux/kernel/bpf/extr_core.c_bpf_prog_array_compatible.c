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
struct bpf_prog {scalar_t__ type; scalar_t__ jited; scalar_t__ kprobe_override; } ;
struct bpf_array {scalar_t__ owner_prog_type; scalar_t__ owner_jited; } ;

/* Variables and functions */

bool bpf_prog_array_compatible(struct bpf_array *array,
			       const struct bpf_prog *fp)
{
	if (fp->kprobe_override)
		return false;

	if (!array->owner_prog_type) {
		/* There's no owner yet where we could check for
		 * compatibility.
		 */
		array->owner_prog_type = fp->type;
		array->owner_jited = fp->jited;

		return true;
	}

	return array->owner_prog_type == fp->type &&
	       array->owner_jited == fp->jited;
}