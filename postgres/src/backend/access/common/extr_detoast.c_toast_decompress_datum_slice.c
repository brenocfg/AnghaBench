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
typedef  scalar_t__ int32 ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  SET_VARSIZE (struct varlena*,scalar_t__) ; 
 scalar_t__ TOAST_COMPRESS_HDRSZ ; 
 int /*<<< orphan*/  TOAST_COMPRESS_RAWDATA (struct varlena*) ; 
 int /*<<< orphan*/  VARATT_IS_COMPRESSED (struct varlena*) ; 
 int /*<<< orphan*/  VARDATA (struct varlena*) ; 
 scalar_t__ VARHDRSZ ; 
 scalar_t__ VARSIZE (struct varlena*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ palloc (scalar_t__) ; 
 scalar_t__ pglz_decompress (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static struct varlena *
toast_decompress_datum_slice(struct varlena *attr, int32 slicelength)
{
	struct varlena *result;
	int32		rawsize;

	Assert(VARATT_IS_COMPRESSED(attr));

	result = (struct varlena *) palloc(slicelength + VARHDRSZ);

	rawsize = pglz_decompress(TOAST_COMPRESS_RAWDATA(attr),
							  VARSIZE(attr) - TOAST_COMPRESS_HDRSZ,
							  VARDATA(result),
							  slicelength, false);
	if (rawsize < 0)
		elog(ERROR, "compressed data is corrupted");

	SET_VARSIZE(result, rawsize + VARHDRSZ);
	return result;
}