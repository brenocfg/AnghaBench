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
struct timeouts {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct timeouts*) ; 
 int /*<<< orphan*/  timeouts_reset (struct timeouts*) ; 

void timeouts_close(struct timeouts *T)
{
    /*
     * NOTE: Delete installed timeouts so timeout_pending() and
     * timeout_expired() worked as expected.
     */
    timeouts_reset(T);

    free(T);
}