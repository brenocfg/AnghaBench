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
 int /*<<< orphan*/  Min (int,int) ; 
 int /*<<< orphan*/ * new_intArrayType (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * resize_intArrayType (int /*<<< orphan*/ *,int) ; 

ArrayType *
inner_int_inter(ArrayType *a, ArrayType *b)
{
	ArrayType  *r;
	int			na,
				nb;
	int		   *da,
			   *db,
			   *dr;
	int			i,
				j,
				k;

	if (ARRISEMPTY(a) || ARRISEMPTY(b))
		return new_intArrayType(0);

	na = ARRNELEMS(a);
	nb = ARRNELEMS(b);
	da = ARRPTR(a);
	db = ARRPTR(b);
	r = new_intArrayType(Min(na, nb));
	dr = ARRPTR(r);

	i = j = k = 0;
	while (i < na && j < nb)
	{
		if (da[i] < db[j])
			i++;
		else if (da[i] == db[j])
		{
			if (k == 0 || dr[k - 1] != db[j])
				dr[k++] = db[j];
			i++;
			j++;
		}
		else
			j++;
	}

	if (k == 0)
	{
		pfree(r);
		return new_intArrayType(0);
	}
	else
		return resize_intArrayType(r, k);
}