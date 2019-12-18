#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ type; } ;
struct TYPE_8__ {int /*<<< orphan*/  len; scalar_t__ data; } ;
typedef  TYPE_1__ StringInfoData ;
typedef  TYPE_2__ JsonbValue ;
typedef  int /*<<< orphan*/  Jsonb ;
typedef  int /*<<< orphan*/  JEntry ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  SET_VARSIZE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VARHDRSZ ; 
 int /*<<< orphan*/  convertJsonbValue (TYPE_1__*,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 
 scalar_t__ jbvBinary ; 
 int /*<<< orphan*/  reserveFromBuffer (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Jsonb *
convertToJsonb(JsonbValue *val)
{
	StringInfoData buffer;
	JEntry		jentry;
	Jsonb	   *res;

	/* Should not already have binary representation */
	Assert(val->type != jbvBinary);

	/* Allocate an output buffer. It will be enlarged as needed */
	initStringInfo(&buffer);

	/* Make room for the varlena header */
	reserveFromBuffer(&buffer, VARHDRSZ);

	convertJsonbValue(&buffer, &jentry, val, 0);

	/*
	 * Note: the JEntry of the root is discarded. Therefore the root
	 * JsonbContainer struct must contain enough information to tell what kind
	 * of value it is.
	 */

	res = (Jsonb *) buffer.data;

	SET_VARSIZE(res, buffer.len);

	return res;
}