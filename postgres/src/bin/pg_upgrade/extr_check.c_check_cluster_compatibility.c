#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ port; int /*<<< orphan*/  major_version; int /*<<< orphan*/  controldata; } ;

/* Variables and functions */
 scalar_t__ DEF_PGUPORT ; 
 int GET_MAJOR_VERSION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_control_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_control_data (TYPE_1__*,int) ; 
 TYPE_1__ new_cluster ; 
 TYPE_1__ old_cluster ; 
 int /*<<< orphan*/  pg_fatal (char*) ; 

void
check_cluster_compatibility(bool live_check)
{
	/* get/check pg_control data of servers */
	get_control_data(&old_cluster, live_check);
	get_control_data(&new_cluster, false);
	check_control_data(&old_cluster.controldata, &new_cluster.controldata);

	/* We read the real port number for PG >= 9.1 */
	if (live_check && GET_MAJOR_VERSION(old_cluster.major_version) < 901 &&
		old_cluster.port == DEF_PGUPORT)
		pg_fatal("When checking a pre-PG 9.1 live old server, "
				 "you must specify the old server's port number.\n");

	if (live_check && old_cluster.port == new_cluster.port)
		pg_fatal("When checking a live server, "
				 "the old and new port numbers must be different.\n");
}