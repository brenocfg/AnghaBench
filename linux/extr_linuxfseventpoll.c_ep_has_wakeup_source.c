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
struct epitem {int /*<<< orphan*/  ws; } ;

/* Variables and functions */
 scalar_t__ rcu_access_pointer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool ep_has_wakeup_source(struct epitem *epi)
{
	return rcu_access_pointer(epi->ws) ? true : false;
}