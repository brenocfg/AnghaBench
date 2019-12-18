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
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  S_ATTACK_TIME ; 
 int /*<<< orphan*/  S_CLOSE_THRESHOLD ; 
 int /*<<< orphan*/  S_HOLD_TIME ; 
 int /*<<< orphan*/  S_OPEN_THRESHOLD ; 
 int /*<<< orphan*/  S_RELEASE_TIME ; 
 int /*<<< orphan*/  obs_data_set_default_double (int /*<<< orphan*/ *,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  obs_data_set_default_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void noise_gate_defaults(obs_data_t *s)
{
	obs_data_set_default_double(s, S_OPEN_THRESHOLD, -26.0);
	obs_data_set_default_double(s, S_CLOSE_THRESHOLD, -32.0);
	obs_data_set_default_int(s, S_ATTACK_TIME, 25);
	obs_data_set_default_int(s, S_HOLD_TIME, 200);
	obs_data_set_default_int(s, S_RELEASE_TIME, 150);
}