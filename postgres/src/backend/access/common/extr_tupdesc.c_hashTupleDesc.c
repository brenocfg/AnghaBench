#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32 ;
typedef  TYPE_1__* TupleDesc ;
struct TYPE_6__ {int atttypid; } ;
struct TYPE_5__ {int natts; int tdtypeid; } ;

/* Variables and functions */
 TYPE_3__* TupleDescAttr (TYPE_1__*,int) ; 
 scalar_t__ hash_combine (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_uint32 (int) ; 

uint32
hashTupleDesc(TupleDesc desc)
{
	uint32		s;
	int			i;

	s = hash_combine(0, hash_uint32(desc->natts));
	s = hash_combine(s, hash_uint32(desc->tdtypeid));
	for (i = 0; i < desc->natts; ++i)
		s = hash_combine(s, hash_uint32(TupleDescAttr(desc, i)->atttypid));

	return s;
}