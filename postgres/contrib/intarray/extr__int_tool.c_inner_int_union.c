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
typedef  int /*<<< orphan*/  ArrayType ;

/* Variables and functions */
 scalar_t__ ARRISEMPTY (int /*<<< orphan*/ *) ; 
 int ARRNELEMS (int /*<<< orphan*/ *) ; 
 int* ARRPTR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CHECKARRVALID (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * _int_unique (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * copy_intArrayType (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * new_intArrayType (int) ; 
 int /*<<< orphan*/ * resize_intArrayType (int /*<<< orphan*/ *,int) ; 

ArrayType *
inner_int_union(ArrayType *a, ArrayType *b)
{
	ArrayType  *r = NULL;

	CHECKARRVALID(a);
	CHECKARRVALID(b);

	if (ARRISEMPTY(a) && ARRISEMPTY(b))
		return new_intArrayType(0);
	if (ARRISEMPTY(a))
		r = copy_intArrayType(b);
	if (ARRISEMPTY(b))
		r = copy_intArrayType(a);

	if (!r)
	{
		int			na = ARRNELEMS(a),
					nb = ARRNELEMS(b);
		int		   *da = ARRPTR(a),
				   *db = ARRPTR(b);
		int			i,
					j,
				   *dr;

		r = new_intArrayType(na + nb);
		dr = ARRPTR(r);

		/* union */
		i = j = 0;
		while (i < na && j < nb)
		{
			if (da[i] == db[j])
			{
				*dr++ = da[i++];
				j++;
			}
			else if (da[i] < db[j])
				*dr++ = da[i++];
			else
				*dr++ = db[j++];
		}

		while (i < na)
			*dr++ = da[i++];
		while (j < nb)
			*dr++ = db[j++];

		r = resize_intArrayType(r, dr - ARRPTR(r));
	}

	if (ARRNELEMS(r) > 1)
		r = _int_unique(r);

	return r;
}