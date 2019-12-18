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
struct inet_timewait_sock {int /*<<< orphan*/  tw_refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  inet_twsk_free (struct inet_timewait_sock*) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 

void inet_twsk_put(struct inet_timewait_sock *tw)
{
	if (refcount_dec_and_test(&tw->tw_refcnt))
		inet_twsk_free(tw);
}