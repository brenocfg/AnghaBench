#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ipv6_stable_secret {int initialized; int /*<<< orphan*/  secret; } ;
struct TYPE_2__ {struct ipv6_stable_secret stable_secret; } ;
struct inet6_dev {TYPE_1__ cnf; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void ipv6_gen_mode_random_init(struct inet6_dev *idev)
{
	struct ipv6_stable_secret *s = &idev->cnf.stable_secret;

	if (s->initialized)
		return;
	s = &idev->cnf.stable_secret;
	get_random_bytes(&s->secret, sizeof(s->secret));
	s->initialized = true;
}