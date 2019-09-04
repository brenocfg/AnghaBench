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
struct xhci_ring {int /*<<< orphan*/  cycle_state; } ;
struct seq_file {scalar_t__ private; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xhci_ring_cycle_show(struct seq_file *s, void *unused)
{
	struct xhci_ring	*ring = *(struct xhci_ring **)s->private;

	seq_printf(s, "%d\n", ring->cycle_state);

	return 0;
}