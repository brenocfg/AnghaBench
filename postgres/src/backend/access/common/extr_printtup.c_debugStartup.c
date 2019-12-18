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
typedef  TYPE_1__* TupleDesc ;
struct TYPE_4__ {int natts; } ;
typedef  int /*<<< orphan*/  DestReceiver ;

/* Variables and functions */
 int /*<<< orphan*/  TupleDescAttr (TYPE_1__*,int) ; 
 int /*<<< orphan*/  printatt (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 

void
debugStartup(DestReceiver *self, int operation, TupleDesc typeinfo)
{
	int			natts = typeinfo->natts;
	int			i;

	/*
	 * show the return type of the tuples
	 */
	for (i = 0; i < natts; ++i)
		printatt((unsigned) i + 1, TupleDescAttr(typeinfo, i), NULL);
	printf("\t----\n");
}