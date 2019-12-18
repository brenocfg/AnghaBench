#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32 ;
struct TYPE_12__ {size_t tif_nfields; TYPE_1__** tif_fields; int /*<<< orphan*/  tif_clientdata; int /*<<< orphan*/ * tif_foundfield; } ;
struct TYPE_11__ {int /*<<< orphan*/  field_tag; } ;
typedef  TYPE_1__ TIFFField ;
typedef  TYPE_2__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,char const*,char*) ; 
 TYPE_1__* TIFFFindField (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIFF_ANY ; 
 scalar_t__ _TIFFCheckMalloc (TYPE_2__*,size_t,int,char const*) ; 
 scalar_t__ _TIFFCheckRealloc (TYPE_2__*,TYPE_1__**,size_t,int,char const*) ; 
 int /*<<< orphan*/  qsort (TYPE_1__**,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tagCompare ; 

int
_TIFFMergeFields(TIFF* tif, const TIFFField info[], uint32 n)
{
	static const char module[] = "_TIFFMergeFields";
	static const char reason[] = "for fields array";
	/* TIFFField** tp; */
	uint32 i;

        tif->tif_foundfield = NULL;

	if (tif->tif_fields && tif->tif_nfields > 0) {
		tif->tif_fields = (TIFFField**)
			_TIFFCheckRealloc(tif, tif->tif_fields,
					  (tif->tif_nfields + n),
					  sizeof(TIFFField *), reason);
	} else {
		tif->tif_fields = (TIFFField **)
			_TIFFCheckMalloc(tif, n, sizeof(TIFFField *),
					 reason);
	}
	if (!tif->tif_fields) {
		TIFFErrorExt(tif->tif_clientdata, module,
			     "Failed to allocate fields array");
		return 0;
	}

	/* tp = tif->tif_fields + tif->tif_nfields; */
	for (i = 0; i < n; i++) {
		const TIFFField *fip =
			TIFFFindField(tif, info[i].field_tag, TIFF_ANY);

                /* only add definitions that aren't already present */
		if (!fip) {
                        tif->tif_fields[tif->tif_nfields] = (TIFFField *) (info+i);
                        tif->tif_nfields++;
                }
	}

        /* Sort the field info by tag number */
	qsort(tif->tif_fields, tif->tif_nfields,
	      sizeof(TIFFField *), tagCompare);

	return n;
}