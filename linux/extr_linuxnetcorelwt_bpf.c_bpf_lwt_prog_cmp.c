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
struct bpf_lwt_prog {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bpf_lwt_prog_cmp(struct bpf_lwt_prog *a, struct bpf_lwt_prog *b)
{
	/* FIXME:
	 * The LWT state is currently rebuilt for delete requests which
	 * results in a new bpf_prog instance. Comparing names for now.
	 */
	if (!a->name && !b->name)
		return 0;

	if (!a->name || !b->name)
		return 1;

	return strcmp(a->name, b->name);
}