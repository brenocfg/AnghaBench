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
typedef  int /*<<< orphan*/  ArrayType ;

/* Variables and functions */
 char* ARR_DATA_PTR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ARR_NULLBITMAP (int /*<<< orphan*/ *) ; 
 int ArrayGetOffset (int,int*,int*,int*) ; 
 int MAXDIM ; 
 int /*<<< orphan*/  array_bitmap_copy (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int) ; 
 int array_copy (char*,int,char*,int,int /*<<< orphan*/ *,int,int,char) ; 
 char* array_seek (char*,int,int /*<<< orphan*/ *,int,int,int,char) ; 
 int /*<<< orphan*/  mda_get_offset_values (int,int*,int*,int*) ; 
 int /*<<< orphan*/  mda_get_prod (int,int*,int*) ; 
 int /*<<< orphan*/  mda_get_range (int,int*,int*,int*) ; 
 int mda_next_tuple (int,int*,int*) ; 

__attribute__((used)) static void
array_extract_slice(ArrayType *newarray,
					int ndim,
					int *dim,
					int *lb,
					char *arraydataptr,
					bits8 *arraynullsptr,
					int *st,
					int *endp,
					int typlen,
					bool typbyval,
					char typalign)
{
	char	   *destdataptr = ARR_DATA_PTR(newarray);
	bits8	   *destnullsptr = ARR_NULLBITMAP(newarray);
	char	   *srcdataptr;
	int			src_offset,
				dest_offset,
				prod[MAXDIM],
				span[MAXDIM],
				dist[MAXDIM],
				indx[MAXDIM];
	int			i,
				j,
				inc;

	src_offset = ArrayGetOffset(ndim, dim, lb, st);
	srcdataptr = array_seek(arraydataptr, 0, arraynullsptr, src_offset,
							typlen, typbyval, typalign);
	mda_get_prod(ndim, dim, prod);
	mda_get_range(ndim, span, st, endp);
	mda_get_offset_values(ndim, dist, prod, span);
	for (i = 0; i < ndim; i++)
		indx[i] = 0;
	dest_offset = 0;
	j = ndim - 1;
	do
	{
		if (dist[j])
		{
			/* skip unwanted elements */
			srcdataptr = array_seek(srcdataptr, src_offset, arraynullsptr,
									dist[j],
									typlen, typbyval, typalign);
			src_offset += dist[j];
		}
		inc = array_copy(destdataptr, 1,
						 srcdataptr, src_offset, arraynullsptr,
						 typlen, typbyval, typalign);
		if (destnullsptr)
			array_bitmap_copy(destnullsptr, dest_offset,
							  arraynullsptr, src_offset,
							  1);
		destdataptr += inc;
		srcdataptr += inc;
		src_offset++;
		dest_offset++;
	} while ((j = mda_next_tuple(ndim, indx, span)) != -1);
}