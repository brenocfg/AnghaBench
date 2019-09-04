#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_4__* iterator; } ;
struct TYPE_8__ {TYPE_2__ inner; } ;
typedef  TYPE_3__ spl_dual_it_object ;
struct TYPE_9__ {TYPE_1__* funcs; } ;
struct TYPE_6__ {int (* valid ) (TYPE_4__*) ;} ;

/* Variables and functions */
 int FAILURE ; 
 int stub1 (TYPE_4__*) ; 

__attribute__((used)) static inline int spl_dual_it_valid(spl_dual_it_object *intern)
{
	if (!intern->inner.iterator) {
		return FAILURE;
	}
	/* FAILURE / SUCCESS */
	return intern->inner.iterator->funcs->valid(intern->inner.iterator);
}