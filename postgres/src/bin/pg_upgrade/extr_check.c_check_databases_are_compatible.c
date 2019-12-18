#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int ndbs; TYPE_3__* dbs; } ;
struct TYPE_12__ {TYPE_2__ dbarr; } ;
struct TYPE_8__ {int ndbs; TYPE_3__* dbs; } ;
struct TYPE_11__ {TYPE_1__ dbarr; } ;
struct TYPE_10__ {int /*<<< orphan*/  db_name; } ;
typedef  TYPE_3__ DbInfo ;

/* Variables and functions */
 int /*<<< orphan*/  check_locale_and_encoding (TYPE_3__*,TYPE_3__*) ; 
 TYPE_5__ new_cluster ; 
 TYPE_4__ old_cluster ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
check_databases_are_compatible(void)
{
	int			newdbnum;
	int			olddbnum;
	DbInfo	   *newdbinfo;
	DbInfo	   *olddbinfo;

	for (newdbnum = 0; newdbnum < new_cluster.dbarr.ndbs; newdbnum++)
	{
		newdbinfo = &new_cluster.dbarr.dbs[newdbnum];

		/* Find the corresponding database in the old cluster */
		for (olddbnum = 0; olddbnum < old_cluster.dbarr.ndbs; olddbnum++)
		{
			olddbinfo = &old_cluster.dbarr.dbs[olddbnum];
			if (strcmp(newdbinfo->db_name, olddbinfo->db_name) == 0)
			{
				check_locale_and_encoding(olddbinfo, newdbinfo);
				break;
			}
		}
	}
}