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
struct signal_info {int /*<<< orphan*/  source; int /*<<< orphan*/ * signal_text; scalar_t__ signal_received; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIG_SOURCE_SOFT ; 

__attribute__((used)) static void
signal_reset(struct signal_info *si)
{
    if (si)
    {
        si->signal_received = 0;
        si->signal_text = NULL;
        si->source = SIG_SOURCE_SOFT;
    }
}