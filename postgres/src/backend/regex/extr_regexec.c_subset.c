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
struct vars {size_t nmatch; TYPE_1__* pmatch; } ;
struct subre {int subno; } ;
typedef  int /*<<< orphan*/  chr ;
struct TYPE_2__ {void* rm_eo; void* rm_so; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDEBUG (char*) ; 
 void* OFF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void
subset(struct vars *v,
	   struct subre *sub,
	   chr *begin,
	   chr *end)
{
	int			n = sub->subno;

	assert(n > 0);
	if ((size_t) n >= v->nmatch)
		return;

	MDEBUG(("setting %d\n", n));
	v->pmatch[n].rm_so = OFF(begin);
	v->pmatch[n].rm_eo = OFF(end);
}