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
 int /*<<< orphan*/  btc8821a1ant_sw_mechanism (struct btc_coexist*,int) ; 

__attribute__((used)) static void btc8821a1ant_action_pan_edr(struct btc_coexist *btcoexist)
{
	btc8821a1ant_sw_mechanism(btcoexist, false);
}