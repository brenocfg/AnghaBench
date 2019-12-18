#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int transfer_mode; } ;

/* Variables and functions */
#define  TRANSFER_MODE_CLONE 130 
#define  TRANSFER_MODE_COPY 129 
#define  TRANSFER_MODE_LINK 128 
 int /*<<< orphan*/  check_databases_are_compatible () ; 
 int /*<<< orphan*/  check_file_clone () ; 
 int /*<<< orphan*/  check_for_prepared_transactions (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_hard_link () ; 
 int /*<<< orphan*/  check_is_install_user (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_loadable_libraries () ; 
 int /*<<< orphan*/  check_new_cluster_is_empty () ; 
 int /*<<< orphan*/  get_db_and_rel_infos (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  new_cluster ; 
 TYPE_1__ user_opts ; 

void
check_new_cluster(void)
{
	get_db_and_rel_infos(&new_cluster);

	check_new_cluster_is_empty();
	check_databases_are_compatible();

	check_loadable_libraries();

	switch (user_opts.transfer_mode)
	{
		case TRANSFER_MODE_CLONE:
			check_file_clone();
			break;
		case TRANSFER_MODE_COPY:
			break;
		case TRANSFER_MODE_LINK:
			check_hard_link();
			break;
	}

	check_is_install_user(&new_cluster);

	check_for_prepared_transactions(&new_cluster);
}