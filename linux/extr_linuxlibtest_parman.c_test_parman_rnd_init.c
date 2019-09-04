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
struct test_parman {int /*<<< orphan*/  rnd; } ;

/* Variables and functions */
 int /*<<< orphan*/  prandom_seed_state (int /*<<< orphan*/ *,unsigned long long) ; 

__attribute__((used)) static void test_parman_rnd_init(struct test_parman *test_parman)
{
	prandom_seed_state(&test_parman->rnd, 3141592653589793238ULL);
}