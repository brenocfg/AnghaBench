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
struct TYPE_2__ {int signal_received; char const* signal_text; int /*<<< orphan*/  source; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIG_SOURCE_SOFT ; 
 TYPE_1__ siginfo_static ; 

void
throw_signal_soft(const int signum, const char *signal_text)
{
    siginfo_static.signal_received = signum;
    siginfo_static.source = SIG_SOURCE_SOFT;
    siginfo_static.signal_text = signal_text;
}