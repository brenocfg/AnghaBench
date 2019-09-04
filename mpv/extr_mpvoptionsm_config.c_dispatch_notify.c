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
struct m_config_cache {int /*<<< orphan*/  wakeup_dispatch_cb_ctx; int /*<<< orphan*/  wakeup_dispatch_cb; int /*<<< orphan*/  wakeup_dispatch_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_dispatch_enqueue_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dispatch_notify(void *p)
{
    struct m_config_cache *cache = p;

    assert(cache->wakeup_dispatch_queue);
    mp_dispatch_enqueue_notify(cache->wakeup_dispatch_queue,
                               cache->wakeup_dispatch_cb,
                               cache->wakeup_dispatch_cb_ctx);
}