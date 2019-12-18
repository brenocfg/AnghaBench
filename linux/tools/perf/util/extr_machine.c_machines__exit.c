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
struct machines {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  machine__exit (int /*<<< orphan*/ *) ; 

void machines__exit(struct machines *machines)
{
	machine__exit(&machines->host);
	/* XXX exit guest */
}