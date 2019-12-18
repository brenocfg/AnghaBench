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
 int /*<<< orphan*/  ARR_DIMS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ARR_NDIM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ARR_NULLBITMAP (int /*<<< orphan*/ *) ; 
 int ArrayGetNItems (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
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
array_insert_slice(ArrayType *destArray,
				   ArrayType *origArray,
				   ArrayType *srcArray,
				   int ndim,
				   int *dim,
				   int *lb,
				   int *st,
				   int *endp,
				   int typlen,
				   bool typbyval,
				   char typalign)
{
	char	   *destPtr = ARR_DATA_PTR(destArray);
	char	   *origPtr = ARR_DATA_PTR(origArray);
	char	   *srcPtr = ARR_DATA_PTR(srcArray);
	bits8	   *destBitmap = ARR_NULLBITMAP(destArray);
	bits8	   *origBitmap = ARR_NULLBITMAP(origArray);
	bits8	   *srcBitmap = ARR_NULLBITMAP(srcArray);
	int			orignitems = ArrayGetNItems(ARR_NDIM(origArray),
											ARR_DIMS(origArray));
	int			dest_offset,
				orig_offset,
				src_offset,
				prod[MAXDIM],
				span[MAXDIM],
				dist[MAXDIM],
				indx[MAXDIM];
	int			i,
				j,
				inc;

	dest_offset = ArrayGetOffset(ndim, dim, lb, st);
	/* copy items before the slice start */
	inc = array_copy(destPtr, dest_offset,
					 origPtr, 0, origBitmap,
					 typlen, typbyval, typalign);
	destPtr += inc;
	origPtr += inc;
	if (destBitmap)
		array_bitmap_copy(destBitmap, 0, origBitmap, 0, dest_offset);
	orig_offset = dest_offset;
	mda_get_prod(ndim, dim, prod);
	mda_get_range(ndim, span, st, endp);
	mda_get_offset_values(ndim, dist, prod, span);
	for (i = 0; i < ndim; i++)
		indx[i] = 0;
	src_offset = 0;
	j = ndim - 1;
	do
	{
		/* Copy/advance over elements between here and next part of slice */
		if (dist[j])
		{
			inc = array_copy(destPtr, dist[j],
							 origPtr, orig_offset, origBitmap,
							 typlen, typbyval, typalign);
			destPtr += inc;
			origPtr += inc;
			if (destBitmap)
				array_bitmap_copy(destBitmap, dest_offset,
								  origBitmap, orig_offset,
								  dist[j]);
			dest_offset += dist[j];
			orig_offset += dist[j];
		}
		/* Copy new element at this slice position */
		inc = array_copy(destPtr, 1,
						 srcPtr, src_offset, srcBitmap,
						 typlen, typbyval, typalign);
		if (destBitmap)
			array_bitmap_copy(destBitmap, dest_offset,
							  srcBitmap, src_offset,
							  1);
		destPtr += inc;
		srcPtr += inc;
		dest_offset++;
		src_offset++;
		/* Advance over old element at this slice position */
		origPtr = array_seek(origPtr, orig_offset, origBitmap, 1,
							 typlen, typbyval, typalign);
		orig_offset++;
	} while ((j = mda_next_tuple(ndim, indx, span)) != -1);

	/* don't miss any data at the end */
	array_copy(destPtr, orignitems - orig_offset,
			   origPtr, orig_offset, origBitmap,
			   typlen, typbyval, typalign);
	if (destBitmap)
		array_bitmap_copy(destBitmap, dest_offset,
						  origBitmap, orig_offset,
						  orignitems - orig_offset);
}