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
struct rhashtable_compare_arg {char** key; } ;
struct aa_data {int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,char const* const) ; 

__attribute__((used)) static int datacmp(struct rhashtable_compare_arg *arg, const void *obj)
{
	const struct aa_data *data = obj;
	const char * const *key = arg->key;

	return strcmp(data->key, *key);
}