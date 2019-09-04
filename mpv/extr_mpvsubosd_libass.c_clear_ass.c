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
struct ass_state {scalar_t__ track; } ;

/* Variables and functions */
 int /*<<< orphan*/  ass_flush_events (scalar_t__) ; 

__attribute__((used)) static void clear_ass(struct ass_state *ass)
{
    if (ass->track)
        ass_flush_events(ass->track);
}