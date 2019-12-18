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

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  SET_VARSIZE (struct varlena*,scalar_t__) ; 
 int /*<<< orphan*/  TOAST_COMPRESS_RAWDATA (struct varlena*) ; 
 scalar_t__ TOAST_COMPRESS_RAWSIZE (struct varlena*) ; 
 int /*<<< orphan*/  TOAST_COMPRESS_SIZE (struct varlena*) ; 
 int /*<<< orphan*/  VARATT_IS_COMPRESSED (struct varlena*) ; 
 int /*<<< orphan*/  VARDATA (struct varlena*) ; 
 scalar_t__ VARHDRSZ ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ palloc (scalar_t__) ; 
 scalar_t__ pglz_decompress (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static struct varlena *
toast_decompress_datum(struct varlena *attr)
{
	struct varlena *result;

	Assert(VARATT_IS_COMPRESSED(attr));

	result = (struct varlena *)
		palloc(TOAST_COMPRESS_RAWSIZE(attr) + VARHDRSZ);
	SET_VARSIZE(result, TOAST_COMPRESS_RAWSIZE(attr) + VARHDRSZ);

	if (pglz_decompress(TOAST_COMPRESS_RAWDATA(attr),
						TOAST_COMPRESS_SIZE(attr),
						VARDATA(result),
						TOAST_COMPRESS_RAWSIZE(attr), true) < 0)
		elog(ERROR, "compressed data is corrupted");

	return result;
}