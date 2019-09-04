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
struct TYPE_2__ {scalar_t__ signal; } ;
struct record {TYPE_1__ switch_output; } ;

/* Variables and functions */
 int /*<<< orphan*/  switch_output_trigger ; 
 scalar_t__ trigger_is_ready (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool switch_output_signal(struct record *rec)
{
	return rec->switch_output.signal &&
	       trigger_is_ready(&switch_output_trigger);
}