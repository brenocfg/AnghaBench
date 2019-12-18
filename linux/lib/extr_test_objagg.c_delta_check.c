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
struct tokey {int id; } ;

/* Variables and functions */
 int MAX_KEY_ID_DIFF ; 

__attribute__((used)) static bool delta_check(void *priv, const void *parent_obj, const void *obj)
{
	const struct tokey *parent_key = parent_obj;
	const struct tokey *key = obj;
	int diff = key->id - parent_key->id;

	return diff >= 0 && diff <= MAX_KEY_ID_DIFF;
}