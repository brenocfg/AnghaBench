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
struct user_namespace {int /*<<< orphan*/  gid_map; } ;
typedef  int /*<<< orphan*/  kgid_t ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  __kgid_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_id_up (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

gid_t from_kgid(struct user_namespace *targ, kgid_t kgid)
{
	/* Map the gid from a global kernel gid */
	return map_id_up(&targ->gid_map, __kgid_val(kgid));
}