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
struct context {int dummy; } ;

/* Variables and functions */
 int process_signal (struct context*) ; 
 int /*<<< orphan*/  remap_signal (struct context*) ; 

__attribute__((used)) static bool
process_signal_p2p(struct context *c)
{
    remap_signal(c);
    return process_signal(c);
}