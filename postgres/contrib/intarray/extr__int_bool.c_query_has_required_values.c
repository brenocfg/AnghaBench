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

/* Variables and functions */
 scalar_t__ GETQUERY (TYPE_1__*) ; 
 int contains_required_value (scalar_t__) ; 

bool
query_has_required_values(QUERYTYPE *query)
{
	if (query->size <= 0)
		return false;
	return contains_required_value(GETQUERY(query) + query->size - 1);
}