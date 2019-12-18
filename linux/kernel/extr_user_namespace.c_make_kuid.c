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
 int /*<<< orphan*/  KUIDT_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_id_down (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

kuid_t make_kuid(struct user_namespace *ns, uid_t uid)
{
	/* Map the uid to a global kernel uid */
	return KUIDT_INIT(map_id_down(&ns->uid_map, uid));
}