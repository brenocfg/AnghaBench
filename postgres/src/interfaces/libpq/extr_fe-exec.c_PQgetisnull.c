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
struct TYPE_6__ {TYPE_1__** tuples; } ;
struct TYPE_5__ {scalar_t__ len; } ;
typedef  TYPE_2__ PGresult ;

/* Variables and functions */
 scalar_t__ NULL_LEN ; 
 int /*<<< orphan*/  check_tuple_field_number (TYPE_2__ const*,int,int) ; 

int
PQgetisnull(const PGresult *res, int tup_num, int field_num)
{
	if (!check_tuple_field_number(res, tup_num, field_num))
		return 1;				/* pretend it is null */
	if (res->tuples[tup_num][field_num].len == NULL_LEN)
		return 1;
	else
		return 0;
}