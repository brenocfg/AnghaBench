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
struct bpf_program {scalar_t__ idx; } ;
struct TYPE_2__ {scalar_t__ text_shndx; } ;
struct bpf_object {scalar_t__ has_pseudo_calls; TYPE_1__ efile; } ;

/* Variables and functions */

__attribute__((used)) static bool bpf_program__is_function_storage(struct bpf_program *prog,
					     struct bpf_object *obj)
{
	return prog->idx == obj->efile.text_shndx && obj->has_pseudo_calls;
}