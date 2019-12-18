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
struct delayed_work {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STATIC_KEY_CHECK_USE (void*) ; 
 int /*<<< orphan*/  flush_delayed_work (struct delayed_work*) ; 

void __static_key_deferred_flush(void *key, struct delayed_work *work)
{
	STATIC_KEY_CHECK_USE(key);
	flush_delayed_work(work);
}