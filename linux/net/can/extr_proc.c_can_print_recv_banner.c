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
struct seq_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static void can_print_recv_banner(struct seq_file *m)
{
	/*
	 *                  can1.  00000000  00000000  00000000
	 *                 .......          0  tp20
	 */
	seq_puts(m, "  device   can_id   can_mask  function"
			"  userdata   matches  ident\n");
}