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
struct varlena {int dummy; } ;
typedef  int /*<<< orphan*/  Size ;

/* Variables and functions */
 scalar_t__ VARATT_IS_EXTENDED (struct varlena*) ; 
 int /*<<< orphan*/  VARSIZE (struct varlena*) ; 
 struct varlena* detoast_attr (struct varlena*) ; 
 int /*<<< orphan*/  memcpy (struct varlena*,struct varlena*,int /*<<< orphan*/ ) ; 
 scalar_t__ palloc (int /*<<< orphan*/ ) ; 

struct varlena *
pg_detoast_datum_copy(struct varlena *datum)
{
	if (VARATT_IS_EXTENDED(datum))
		return detoast_attr(datum);
	else
	{
		/* Make a modifiable copy of the varlena object */
		Size		len = VARSIZE(datum);
		struct varlena *result = (struct varlena *) palloc(len);

		memcpy(result, datum, len);
		return result;
	}
}