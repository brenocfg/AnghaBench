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
typedef  int /*<<< orphan*/  bits8 ;

/* Variables and functions */
 int ArrayGetNItems (int,int*) ; 
 int ArrayGetOffset (int,int*,int*,int*) ; 
 int MAXDIM ; 
 int /*<<< orphan*/  array_get_isnull (int /*<<< orphan*/ *,int) ; 
 char* array_seek (char*,int,int /*<<< orphan*/ *,int,int,int,char) ; 
 int att_addlength_pointer (int /*<<< orphan*/ ,int,char*) ; 
 int att_align_nominal (int,char) ; 
 int /*<<< orphan*/  mda_get_offset_values (int,int*,int*,int*) ; 
 int /*<<< orphan*/  mda_get_prod (int,int*,int*) ; 
 int /*<<< orphan*/  mda_get_range (int,int*,int*,int*) ; 
 int mda_next_tuple (int,int*,int*) ; 

__attribute__((used)) static int
array_slice_size(char *arraydataptr, bits8 *arraynullsptr,
				 int ndim, int *dim, int *lb,
				 int *st, int *endp,
				 int typlen, bool typbyval, char typalign)
{
	int			src_offset,
				span[MAXDIM],
				prod[MAXDIM],
				dist[MAXDIM],
				indx[MAXDIM];
	char	   *ptr;
	int			i,
				j,
				inc;
	int			count = 0;

	mda_get_range(ndim, span, st, endp);

	/* Pretty easy for fixed element length without nulls ... */
	if (typlen > 0 && !arraynullsptr)
		return ArrayGetNItems(ndim, span) * att_align_nominal(typlen, typalign);

	/* Else gotta do it the hard way */
	src_offset = ArrayGetOffset(ndim, dim, lb, st);
	ptr = array_seek(arraydataptr, 0, arraynullsptr, src_offset,
					 typlen, typbyval, typalign);
	mda_get_prod(ndim, dim, prod);
	mda_get_offset_values(ndim, dist, prod, span);
	for (i = 0; i < ndim; i++)
		indx[i] = 0;
	j = ndim - 1;
	do
	{
		if (dist[j])
		{
			ptr = array_seek(ptr, src_offset, arraynullsptr, dist[j],
							 typlen, typbyval, typalign);
			src_offset += dist[j];
		}
		if (!array_get_isnull(arraynullsptr, src_offset))
		{
			inc = att_addlength_pointer(0, typlen, ptr);
			inc = att_align_nominal(inc, typalign);
			ptr += inc;
			count += inc;
		}
		src_offset++;
	} while ((j = mda_next_tuple(ndim, indx, span)) != -1);
	return count;
}