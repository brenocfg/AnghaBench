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
 int /*<<< orphan*/  S_GAIN_DB ; 
 int /*<<< orphan*/  obs_data_set_default_double (int /*<<< orphan*/ *,int /*<<< orphan*/ ,float) ; 

__attribute__((used)) static void gain_defaults(obs_data_t *s)
{
	obs_data_set_default_double(s, S_GAIN_DB, 0.0f);
}