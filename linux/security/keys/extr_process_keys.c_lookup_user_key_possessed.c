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
struct key_match_data {struct key const* raw_data; } ;
struct key {int dummy; } ;

/* Variables and functions */

bool lookup_user_key_possessed(const struct key *key,
			       const struct key_match_data *match_data)
{
	return key == match_data->raw_data;
}