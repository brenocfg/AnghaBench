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
typedef  int /*<<< orphan*/  uint64_t ;
struct rds_info_iterator {int dummy; } ;
struct rds_info_counter {char* name; int /*<<< orphan*/  value; } ;
typedef  int /*<<< orphan*/  ctr ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  rds_info_copy (struct rds_info_iterator*,struct rds_info_counter*,int) ; 
 int strlen (char const* const) ; 
 int /*<<< orphan*/  strncpy (char*,char const* const,int) ; 

void rds_stats_info_copy(struct rds_info_iterator *iter,
			 uint64_t *values, const char *const *names, size_t nr)
{
	struct rds_info_counter ctr;
	size_t i;

	for (i = 0; i < nr; i++) {
		BUG_ON(strlen(names[i]) >= sizeof(ctr.name));
		strncpy(ctr.name, names[i], sizeof(ctr.name) - 1);
		ctr.name[sizeof(ctr.name) - 1] = '\0';
		ctr.value = values[i];

		rds_info_copy(iter, &ctr, sizeof(ctr));
	}
}