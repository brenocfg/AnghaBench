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
struct btc_coexist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FORCE_EXEC ; 
 int /*<<< orphan*/  btc8821a1ant_coex_table_with_type (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btc8821a1ant_sw_mechanism (struct btc_coexist*,int) ; 

__attribute__((used)) static void btc8821a1ant_init_coex_dm(struct btc_coexist *btcoexist)
{
	/* force to reset coex mechanism
	 * sw all off
	 */
	btc8821a1ant_sw_mechanism(btcoexist, false);

	btc8821a1ant_coex_table_with_type(btcoexist, FORCE_EXEC, 0);
}