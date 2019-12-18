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
typedef  int /*<<< orphan*/  GucSource ;

/* Variables and functions */
 int /*<<< orphan*/  pg_clean_ascii (char*) ; 

__attribute__((used)) static bool
check_cluster_name(char **newval, void **extra, GucSource source)
{
	/* Only allow clean ASCII chars in the cluster name */
	pg_clean_ascii(*newval);

	return true;
}