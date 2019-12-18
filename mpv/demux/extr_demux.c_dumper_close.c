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
struct demux_internal {scalar_t__ dumper_status; int /*<<< orphan*/ * dumper; } ;

/* Variables and functions */
 scalar_t__ CONTROL_FALSE ; 
 scalar_t__ CONTROL_TRUE ; 
 int /*<<< orphan*/  mp_recorder_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dumper_close(struct demux_internal *in)
{
    if (in->dumper)
        mp_recorder_destroy(in->dumper);
    in->dumper = NULL;
    if (in->dumper_status == CONTROL_TRUE)
        in->dumper_status = CONTROL_FALSE; // make abort equal to success
}