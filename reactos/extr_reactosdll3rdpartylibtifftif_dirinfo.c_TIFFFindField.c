#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32 ;
struct TYPE_7__ {TYPE_1__ const* tif_foundfield; int /*<<< orphan*/  tif_nfields; int /*<<< orphan*/  tif_fields; } ;
struct TYPE_6__ {scalar_t__ field_tag; scalar_t__ field_type; int /*<<< orphan*/ * member_11; int /*<<< orphan*/ * member_10; int /*<<< orphan*/  member_9; int /*<<< orphan*/  member_8; int /*<<< orphan*/  member_7; int /*<<< orphan*/  member_6; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ TIFFField ;
typedef  scalar_t__ TIFFDataType ;
typedef  TYPE_2__ TIFF ;

/* Variables and functions */
 scalar_t__ TIFF_ANY ; 
 int /*<<< orphan*/  TIFF_NOTYPE ; 
 scalar_t__ bsearch (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tagCompare ; 

const TIFFField*
TIFFFindField(TIFF* tif, uint32 tag, TIFFDataType dt)
{
	TIFFField key = {0, 0, 0, TIFF_NOTYPE, 0, 0, 0, 0, 0, 0, NULL, NULL};
	TIFFField* pkey = &key;
	const TIFFField **ret;
	if (tif->tif_foundfield && tif->tif_foundfield->field_tag == tag &&
	    (dt == TIFF_ANY || dt == tif->tif_foundfield->field_type))
		return tif->tif_foundfield;

	/* If we are invoked with no field information, then just return. */
	if (!tif->tif_fields)
		return NULL;

	/* NB: use sorted search (e.g. binary search) */

	key.field_tag = tag;
	key.field_type = dt;

	ret = (const TIFFField **) bsearch(&pkey, tif->tif_fields,
					   tif->tif_nfields,
					   sizeof(TIFFField *), tagCompare);
	return tif->tif_foundfield = (ret ? *ret : NULL);
}