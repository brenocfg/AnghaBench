#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_3__ {int /*<<< orphan*/  t_info; } ;
typedef  TYPE_1__* IndexTuple ;

/* Variables and functions */
 int IndexInfoFindDataOffset (int /*<<< orphan*/ ) ; 

uint32
_hash_get_indextuple_hashkey(IndexTuple itup)
{
	char	   *attp;

	/*
	 * We assume the hash key is the first attribute and can't be null, so
	 * this can be done crudely but very very cheaply ...
	 */
	attp = (char *) itup + IndexInfoFindDataOffset(itup->t_info);
	return *((uint32 *) attp);
}