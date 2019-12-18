#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct timer_list {int dummy; } ;
typedef  int /*<<< orphan*/  entropy ;
struct TYPE_3__ {int /*<<< orphan*/  expires; } ;

/* Variables and functions */
 unsigned long MSEC_PER_SEC ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  msecs_to_jiffies (unsigned long) ; 
 int /*<<< orphan*/  prandom_seed (int /*<<< orphan*/ ) ; 
 int prandom_u32_max (int) ; 
 TYPE_1__ seed_timer ; 

__attribute__((used)) static void __prandom_timer(struct timer_list *unused)
{
	u32 entropy;
	unsigned long expires;

	get_random_bytes(&entropy, sizeof(entropy));
	prandom_seed(entropy);

	/* reseed every ~60 seconds, in [40 .. 80) interval with slack */
	expires = 40 + prandom_u32_max(40);
	seed_timer.expires = jiffies + msecs_to_jiffies(expires * MSEC_PER_SEC);

	add_timer(&seed_timer);
}