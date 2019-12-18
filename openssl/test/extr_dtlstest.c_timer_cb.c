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
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  timer_cb_count ; 

__attribute__((used)) static unsigned int timer_cb(SSL *s, unsigned int timer_us)
{
    ++timer_cb_count;

    if (timer_us == 0)
        return 50000;
    else
        return 2 * timer_us;
}