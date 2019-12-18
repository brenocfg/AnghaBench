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
 int /*<<< orphan*/  S_OUTPUT_GAIN ; 
 int /*<<< orphan*/  S_RATIO ; 
 int /*<<< orphan*/  S_RELEASE_TIME ; 
 int /*<<< orphan*/  S_SIDECHAIN_SOURCE ; 
 int /*<<< orphan*/  S_THRESHOLD ; 
 int /*<<< orphan*/  obs_data_set_default_double (int /*<<< orphan*/ *,int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  obs_data_set_default_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  obs_data_set_default_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void compressor_defaults(obs_data_t *s)
{
	obs_data_set_default_double(s, S_RATIO, 10.0f);
	obs_data_set_default_double(s, S_THRESHOLD, -18.0f);
	obs_data_set_default_int(s, S_ATTACK_TIME, 6);
	obs_data_set_default_int(s, S_RELEASE_TIME, 60);
	obs_data_set_default_double(s, S_OUTPUT_GAIN, 0.0f);
	obs_data_set_default_string(s, S_SIDECHAIN_SOURCE, "none");
}