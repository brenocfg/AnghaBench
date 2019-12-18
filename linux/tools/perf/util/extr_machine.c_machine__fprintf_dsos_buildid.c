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
struct TYPE_2__ {int /*<<< orphan*/  head; } ;
struct machine {TYPE_1__ dsos; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t __dsos__fprintf_buildid (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int (*) (struct dso*,int),int) ; 

size_t machine__fprintf_dsos_buildid(struct machine *m, FILE *fp,
				     bool (skip)(struct dso *dso, int parm), int parm)
{
	return __dsos__fprintf_buildid(&m->dsos.head, fp, skip, parm);
}