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
typedef  int /*<<< orphan*/  POLLINFO ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*) ; 

__attribute__((used)) static int statsd_snd_callback(POLLINFO *pi, short int *events) {
    (void)pi;
    (void)events;

    error("STATSD: snd_callback() called, but we never requested to send data to statsd clients.");
    return -1;
}