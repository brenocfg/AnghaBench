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
struct seq_file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int /*<<< orphan*/  print_graph_headers_flags (struct seq_file*,int /*<<< orphan*/ ) ; 
 TYPE_1__ tracer_flags ; 

__attribute__((used)) static void print_graph_headers(struct seq_file *s)
{
	print_graph_headers_flags(s, tracer_flags.val);
}