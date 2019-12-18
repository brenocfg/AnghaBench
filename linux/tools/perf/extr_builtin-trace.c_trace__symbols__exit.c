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
struct trace {int /*<<< orphan*/ * host; } ;

/* Variables and functions */
 int /*<<< orphan*/  machine__exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  symbol__exit () ; 

__attribute__((used)) static void trace__symbols__exit(struct trace *trace)
{
	machine__exit(trace->host);
	trace->host = NULL;

	symbol__exit();
}