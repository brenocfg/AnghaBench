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
struct key_match_data {int /*<<< orphan*/  raw_data; } ;
struct key {int /*<<< orphan*/  description; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool key_default_cmp(const struct key *key,
		     const struct key_match_data *match_data)
{
	return strcmp(key->description, match_data->raw_data) == 0;
}