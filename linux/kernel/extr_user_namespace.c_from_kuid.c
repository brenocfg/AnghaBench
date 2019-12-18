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
typedef  int /*<<< orphan*/  uid_t ;
struct user_namespace {int /*<<< orphan*/  uid_map; } ;
typedef  int /*<<< orphan*/  kuid_t ;

/* Variables and functions */
 int /*<<< orphan*/  __kuid_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_id_up (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

uid_t from_kuid(struct user_namespace *targ, kuid_t kuid)
{
	/* Map the uid from a global kernel uid */
	return map_id_up(&targ->uid_map, __kuid_val(kuid));
}