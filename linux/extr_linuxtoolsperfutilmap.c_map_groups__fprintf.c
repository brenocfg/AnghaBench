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
 size_t maps__fprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

size_t map_groups__fprintf(struct map_groups *mg, FILE *fp)
{
	return maps__fprintf(&mg->maps, fp);
}