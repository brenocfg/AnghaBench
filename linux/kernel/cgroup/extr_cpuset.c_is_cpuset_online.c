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
struct cpuset {int /*<<< orphan*/  css; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_ONLINE ; 
 int /*<<< orphan*/  css_is_dying (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool is_cpuset_online(struct cpuset *cs)
{
	return test_bit(CS_ONLINE, &cs->flags) && !css_is_dying(&cs->css);
}