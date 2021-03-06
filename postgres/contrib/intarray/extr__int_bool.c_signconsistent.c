#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ size; } ;
typedef  TYPE_1__ QUERYTYPE ;
typedef  scalar_t__ BITVEC ;

/* Variables and functions */
 scalar_t__ GETQUERY (TYPE_1__*) ; 
 int /*<<< orphan*/  checkcondition_bit ; 
 int execute (scalar_t__,void*,int,int /*<<< orphan*/ ) ; 

bool
signconsistent(QUERYTYPE *query, BITVEC sign, bool calcnot)
{
	return execute(GETQUERY(query) + query->size - 1,
				   (void *) sign, calcnot,
				   checkcondition_bit);
}