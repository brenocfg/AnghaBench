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
typedef  int /*<<< orphan*/  timeout_t ;
struct timeouts {int /*<<< orphan*/  expired; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timeouts_int (struct timeouts*) ; 

timeout_t timeouts_timeout(struct timeouts *T)
{
    if (!list_empty(&T->expired))
        return 0;

    return timeouts_int(T);
}