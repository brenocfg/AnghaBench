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
struct bpf_lwt_prog {int /*<<< orphan*/  name; scalar_t__ prog; } ;

/* Variables and functions */
 int /*<<< orphan*/  bpf_prog_put (scalar_t__) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bpf_lwt_prog_destroy(struct bpf_lwt_prog *prog)
{
	if (prog->prog)
		bpf_prog_put(prog->prog);

	kfree(prog->name);
}