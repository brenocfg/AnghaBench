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
struct m_config_cache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  m_config_cache_set_dispatch_change_cb (struct m_config_cache*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_config_cache_set_wakeup_cb (struct m_config_cache*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cache_destroy(void *p)
{
    struct m_config_cache *cache = p;

    // (technically speaking, being able to call them both without anything
    // breaking is a feature provided by these functions)
    m_config_cache_set_wakeup_cb(cache, NULL, NULL);
    m_config_cache_set_dispatch_change_cb(cache, NULL, NULL, NULL);
}