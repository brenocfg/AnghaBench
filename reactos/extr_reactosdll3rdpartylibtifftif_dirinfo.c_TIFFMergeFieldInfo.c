#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32 ;
struct TYPE_15__ {scalar_t__ tif_nfieldscompat; int /*<<< orphan*/  tif_clientdata; TYPE_2__* tif_fieldscompat; } ;
struct TYPE_14__ {int /*<<< orphan*/ * field_subfields; int /*<<< orphan*/  field_name; int /*<<< orphan*/  field_passcount; int /*<<< orphan*/  field_oktochange; int /*<<< orphan*/  field_bit; void* get_field_type; void* set_field_type; scalar_t__ reserved; int /*<<< orphan*/  field_type; int /*<<< orphan*/  field_writecount; int /*<<< orphan*/  field_readcount; int /*<<< orphan*/  field_tag; } ;
struct TYPE_13__ {size_t allocated_size; size_t count; TYPE_3__* fields; int /*<<< orphan*/  type; } ;
struct TYPE_12__ {int /*<<< orphan*/  field_name; int /*<<< orphan*/  field_passcount; int /*<<< orphan*/  field_oktochange; int /*<<< orphan*/  field_bit; int /*<<< orphan*/  field_readcount; int /*<<< orphan*/  field_type; int /*<<< orphan*/  field_writecount; int /*<<< orphan*/  field_tag; } ;
typedef  TYPE_1__ TIFFFieldInfo ;
typedef  TYPE_2__ TIFFFieldArray ;
typedef  TYPE_3__ TIFFField ;
typedef  TYPE_4__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,char const*,char*) ; 
 scalar_t__ _TIFFCheckMalloc (TYPE_4__*,size_t,int,char const*) ; 
 scalar_t__ _TIFFCheckRealloc (TYPE_4__*,TYPE_2__*,scalar_t__,int,char const*) ; 
 int /*<<< orphan*/  _TIFFMergeFields (TYPE_4__*,TYPE_3__*,size_t) ; 
 void* _TIFFSetGetType (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tfiatOther ; 

int
TIFFMergeFieldInfo(TIFF* tif, const TIFFFieldInfo info[], uint32 n)
{
	static const char module[] = "TIFFMergeFieldInfo";
	static const char reason[] = "for fields array";
	TIFFField *tp;
	size_t nfields;
	uint32 i;

	if (tif->tif_nfieldscompat > 0) {
		tif->tif_fieldscompat = (TIFFFieldArray *)
			_TIFFCheckRealloc(tif, tif->tif_fieldscompat,
					  tif->tif_nfieldscompat + 1,
					  sizeof(TIFFFieldArray), reason);
	} else {
		tif->tif_fieldscompat = (TIFFFieldArray *)
			_TIFFCheckMalloc(tif, 1, sizeof(TIFFFieldArray),
					 reason);
	}
	if (!tif->tif_fieldscompat) {
		TIFFErrorExt(tif->tif_clientdata, module,
			     "Failed to allocate fields array");
		return -1;
	}
	nfields = tif->tif_nfieldscompat++;

	tif->tif_fieldscompat[nfields].type = tfiatOther;
	tif->tif_fieldscompat[nfields].allocated_size = n;
	tif->tif_fieldscompat[nfields].count = n;
	tif->tif_fieldscompat[nfields].fields =
		(TIFFField *)_TIFFCheckMalloc(tif, n, sizeof(TIFFField),
					      reason);
	if (!tif->tif_fieldscompat[nfields].fields) {
		TIFFErrorExt(tif->tif_clientdata, module,
			     "Failed to allocate fields array");
		return -1;
	}

	tp = tif->tif_fieldscompat[nfields].fields;
	for (i = 0; i < n; i++) {
		tp->field_tag = info[i].field_tag;
		tp->field_readcount = info[i].field_readcount;
		tp->field_writecount = info[i].field_writecount;
		tp->field_type = info[i].field_type;
		tp->reserved = 0;
		tp->set_field_type =
		     _TIFFSetGetType(info[i].field_type,
				info[i].field_readcount,
				info[i].field_passcount);
		tp->get_field_type =
		     _TIFFSetGetType(info[i].field_type,
				info[i].field_readcount,
				info[i].field_passcount);
		tp->field_bit = info[i].field_bit;
		tp->field_oktochange = info[i].field_oktochange;
		tp->field_passcount = info[i].field_passcount;
		tp->field_name = info[i].field_name;
		tp->field_subfields = NULL;
		tp++;
	}

	if (!_TIFFMergeFields(tif, tif->tif_fieldscompat[nfields].fields, n)) {
		TIFFErrorExt(tif->tif_clientdata, module,
			     "Setting up field info failed");
		return -1;
	}

	return 0;
}