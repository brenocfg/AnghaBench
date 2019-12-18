#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* rd_indam; } ;
struct TYPE_5__ {int (* amcanreturn ) (TYPE_2__*,int) ;} ;
typedef  TYPE_2__* Relation ;

/* Variables and functions */
 int /*<<< orphan*/  RELATION_CHECKS ; 
 int stub1 (TYPE_2__*,int) ; 

bool
index_can_return(Relation indexRelation, int attno)
{
	RELATION_CHECKS;

	/* amcanreturn is optional; assume false if not provided by AM */
	if (indexRelation->rd_indam->amcanreturn == NULL)
		return false;

	return indexRelation->rd_indam->amcanreturn(indexRelation, attno);
}