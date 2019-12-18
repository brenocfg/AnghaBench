#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  bytea ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  Const ;

/* Variables and functions */
 int /*<<< orphan*/  BYTEAOID ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SET_VARSIZE (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  VARDATA (int /*<<< orphan*/ *) ; 
 scalar_t__ VARHDRSZ ; 
 int /*<<< orphan*/ * makeConst (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,size_t) ; 
 int /*<<< orphan*/ * palloc (scalar_t__) ; 

__attribute__((used)) static Const *
string_to_bytea_const(const char *str, size_t str_len)
{
	bytea	   *bstr = palloc(VARHDRSZ + str_len);
	Datum		conval;

	memcpy(VARDATA(bstr), str, str_len);
	SET_VARSIZE(bstr, VARHDRSZ + str_len);
	conval = PointerGetDatum(bstr);

	return makeConst(BYTEAOID, -1, InvalidOid, -1, conval, false, false);
}