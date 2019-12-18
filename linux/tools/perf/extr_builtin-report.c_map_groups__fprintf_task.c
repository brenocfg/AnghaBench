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
struct map_groups {int /*<<< orphan*/  maps; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int maps__fprintf_task (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int map_groups__fprintf_task(struct map_groups *mg, int indent, FILE *fp)
{
	return maps__fprintf_task(&mg->maps, indent, fp);
}