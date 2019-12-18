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
typedef  int /*<<< orphan*/  int16 ;
typedef  int bits8 ;
typedef  int /*<<< orphan*/  ArrayType ;

/* Variables and functions */
 char* ARR_DATA_PTR (int /*<<< orphan*/ *) ; 
 int* ARR_DIMS (int /*<<< orphan*/ *) ; 
 scalar_t__ ARR_ELEMTYPE (int /*<<< orphan*/ *) ; 
 int ARR_NDIM (int /*<<< orphan*/ *) ; 
 int* ARR_NULLBITMAP (int /*<<< orphan*/ *) ; 
 int ArrayGetNItems (int,int*) ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  PointerGetDatum (char*) ; 
 scalar_t__ TEXTOID ; 
 char* TextDatumGetCString (int /*<<< orphan*/ ) ; 
 char* att_addlength_pointer (char*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ att_align_nominal (char*,char) ; 
 int /*<<< orphan*/  get_typlenbyvalalign (scalar_t__,int /*<<< orphan*/ *,int*,char*) ; 
 scalar_t__ palloc (int) ; 

__attribute__((used)) static char **
get_text_array_contents(ArrayType *array, int *numitems)
{
	int			ndim = ARR_NDIM(array);
	int		   *dims = ARR_DIMS(array);
	int			nitems;
	int16		typlen;
	bool		typbyval;
	char		typalign;
	char	  **values;
	char	   *ptr;
	bits8	   *bitmap;
	int			bitmask;
	int			i;

	Assert(ARR_ELEMTYPE(array) == TEXTOID);

	*numitems = nitems = ArrayGetNItems(ndim, dims);

	get_typlenbyvalalign(ARR_ELEMTYPE(array),
						 &typlen, &typbyval, &typalign);

	values = (char **) palloc(nitems * sizeof(char *));

	ptr = ARR_DATA_PTR(array);
	bitmap = ARR_NULLBITMAP(array);
	bitmask = 1;

	for (i = 0; i < nitems; i++)
	{
		if (bitmap && (*bitmap & bitmask) == 0)
		{
			values[i] = NULL;
		}
		else
		{
			values[i] = TextDatumGetCString(PointerGetDatum(ptr));
			ptr = att_addlength_pointer(ptr, typlen, ptr);
			ptr = (char *) att_align_nominal(ptr, typalign);
		}

		/* advance bitmap pointer if any */
		if (bitmap)
		{
			bitmask <<= 1;
			if (bitmask == 0x100)
			{
				bitmap++;
				bitmask = 1;
			}
		}
	}

	return values;
}