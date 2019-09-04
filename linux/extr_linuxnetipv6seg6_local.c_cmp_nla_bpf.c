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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct seg6_local_lwt {TYPE_1__ bpf; } ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cmp_nla_bpf(struct seg6_local_lwt *a, struct seg6_local_lwt *b)
{
	if (!a->bpf.name && !b->bpf.name)
		return 0;

	if (!a->bpf.name || !b->bpf.name)
		return 1;

	return strcmp(a->bpf.name, b->bpf.name);
}