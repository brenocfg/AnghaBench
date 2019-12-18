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
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  ArrayType ;

/* Variables and functions */
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REGTYPEOID ; 
 int /*<<< orphan*/ * construct_array (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int,char) ; 
 scalar_t__ palloc (int) ; 

__attribute__((used)) static Datum
build_regtype_array(Oid *param_types, int num_params)
{
	Datum	   *tmp_ary;
	ArrayType  *result;
	int			i;

	tmp_ary = (Datum *) palloc(num_params * sizeof(Datum));

	for (i = 0; i < num_params; i++)
		tmp_ary[i] = ObjectIdGetDatum(param_types[i]);

	/* XXX: this hardcodes assumptions about the regtype type */
	result = construct_array(tmp_ary, num_params, REGTYPEOID, 4, true, 'i');
	return PointerGetDatum(result);
}