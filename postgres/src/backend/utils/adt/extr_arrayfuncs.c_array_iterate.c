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
struct TYPE_3__ {scalar_t__ current_item; scalar_t__ nitems; scalar_t__ slice_ndim; char* data_ptr; int* slice_nulls; int slice_len; int /*<<< orphan*/  typalign; int /*<<< orphan*/  typbyval; int /*<<< orphan*/  typlen; int /*<<< orphan*/  arr; int /*<<< orphan*/  slice_lbound; int /*<<< orphan*/  slice_dims; int /*<<< orphan*/  nullbitmap; scalar_t__* slice_values; } ;
typedef  scalar_t__ Datum ;
typedef  int /*<<< orphan*/  ArrayType ;
typedef  TYPE_1__* ArrayIterator ;

/* Variables and functions */
 int /*<<< orphan*/  ARR_ELEMTYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ PointerGetDatum (int /*<<< orphan*/ *) ; 
 scalar_t__ array_get_isnull (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* att_addlength_pointer (char*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ att_align_nominal (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * construct_md_array (scalar_t__*,int*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fetch_att (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
array_iterate(ArrayIterator iterator, Datum *value, bool *isnull)
{
	/* Done if we have reached the end of the array */
	if (iterator->current_item >= iterator->nitems)
		return false;

	if (iterator->slice_ndim == 0)
	{
		/*
		 * Scalar case: return one element.
		 */
		if (array_get_isnull(iterator->nullbitmap, iterator->current_item++))
		{
			*isnull = true;
			*value = (Datum) 0;
		}
		else
		{
			/* non-NULL, so fetch the individual Datum to return */
			char	   *p = iterator->data_ptr;

			*isnull = false;
			*value = fetch_att(p, iterator->typbyval, iterator->typlen);

			/* Move our data pointer forward to the next element */
			p = att_addlength_pointer(p, iterator->typlen, p);
			p = (char *) att_align_nominal(p, iterator->typalign);
			iterator->data_ptr = p;
		}
	}
	else
	{
		/*
		 * Slice case: build and return an array of the requested size.
		 */
		ArrayType  *result;
		Datum	   *values = iterator->slice_values;
		bool	   *nulls = iterator->slice_nulls;
		char	   *p = iterator->data_ptr;
		int			i;

		for (i = 0; i < iterator->slice_len; i++)
		{
			if (array_get_isnull(iterator->nullbitmap,
								 iterator->current_item++))
			{
				nulls[i] = true;
				values[i] = (Datum) 0;
			}
			else
			{
				nulls[i] = false;
				values[i] = fetch_att(p, iterator->typbyval, iterator->typlen);

				/* Move our data pointer forward to the next element */
				p = att_addlength_pointer(p, iterator->typlen, p);
				p = (char *) att_align_nominal(p, iterator->typalign);
			}
		}

		iterator->data_ptr = p;

		result = construct_md_array(values,
									nulls,
									iterator->slice_ndim,
									iterator->slice_dims,
									iterator->slice_lbound,
									ARR_ELEMTYPE(iterator->arr),
									iterator->typlen,
									iterator->typbyval,
									iterator->typalign);

		*isnull = false;
		*value = PointerGetDatum(result);
	}

	return true;
}