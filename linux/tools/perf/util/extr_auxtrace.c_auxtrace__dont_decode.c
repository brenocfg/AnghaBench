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
struct perf_session {TYPE_1__* itrace_synth_opts; } ;
struct TYPE_2__ {scalar_t__ dont_decode; } ;

/* Variables and functions */

__attribute__((used)) static bool auxtrace__dont_decode(struct perf_session *session)
{
	return !session->itrace_synth_opts ||
	       session->itrace_synth_opts->dont_decode;
}