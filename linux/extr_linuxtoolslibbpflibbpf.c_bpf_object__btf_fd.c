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
struct bpf_object {scalar_t__ btf; } ;

/* Variables and functions */
 int btf__fd (scalar_t__) ; 

int bpf_object__btf_fd(const struct bpf_object *obj)
{
	return obj->btf ? btf__fd(obj->btf) : -1;
}