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
typedef  int /*<<< orphan*/  u32 ;
struct test_parman {int /*<<< orphan*/  rnd; } ;

/* Variables and functions */
 int /*<<< orphan*/  prandom_u32_state (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 test_parman_rnd_get(struct test_parman *test_parman)
{
	return prandom_u32_state(&test_parman->rnd);
}