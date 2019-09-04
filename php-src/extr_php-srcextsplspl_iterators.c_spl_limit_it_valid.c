#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int count; scalar_t__ offset; } ;
struct TYPE_9__ {TYPE_2__ limit; } ;
struct TYPE_7__ {scalar_t__ pos; } ;
struct TYPE_10__ {TYPE_3__ u; TYPE_1__ current; } ;
typedef  TYPE_4__ spl_dual_it_object ;

/* Variables and functions */
 int FAILURE ; 
 int spl_dual_it_valid (TYPE_4__*) ; 

__attribute__((used)) static inline int spl_limit_it_valid(spl_dual_it_object *intern)
{
	/* FAILURE / SUCCESS */
	if (intern->u.limit.count != -1 && intern->current.pos >= intern->u.limit.offset + intern->u.limit.count) {
		return FAILURE;
	} else {
		return spl_dual_it_valid(intern);
	}
}