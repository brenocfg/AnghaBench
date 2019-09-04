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
struct user_namespace {int /*<<< orphan*/  projid_map; } ;
typedef  int /*<<< orphan*/  projid_t ;
typedef  int /*<<< orphan*/  kprojid_t ;

/* Variables and functions */
 int /*<<< orphan*/  KPROJIDT_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_id_down (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

kprojid_t make_kprojid(struct user_namespace *ns, projid_t projid)
{
	/* Map the uid to a global kernel uid */
	return KPROJIDT_INIT(map_id_down(&ns->projid_map, projid));
}