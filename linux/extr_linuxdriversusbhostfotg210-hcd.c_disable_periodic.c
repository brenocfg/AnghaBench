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
struct fotg210_hcd {scalar_t__ periodic_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  fotg210_poll_PSS (struct fotg210_hcd*) ; 

__attribute__((used)) static void disable_periodic(struct fotg210_hcd *fotg210)
{
	if (--fotg210->periodic_count)
		return;

	/* Don't turn off the schedule until PSS is 1 */
	fotg210_poll_PSS(fotg210);
}