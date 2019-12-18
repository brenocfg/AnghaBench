#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_18__ {scalar_t__ trnc; } ;
typedef  TYPE_2__ gbtree_vinfo ;
struct TYPE_19__ {int /*<<< orphan*/ * flinfo; int /*<<< orphan*/  collation; TYPE_2__ const* tinfo; } ;
typedef  TYPE_3__ gbt_vsrt_arg ;
typedef  int /*<<< orphan*/  bytea ;
struct TYPE_20__ {int i; int /*<<< orphan*/ * t; } ;
typedef  TYPE_4__ Vsrt ;
struct TYPE_23__ {scalar_t__ lower; scalar_t__ upper; } ;
struct TYPE_22__ {int* spl_left; int* spl_right; size_t spl_nleft; size_t spl_nright; void* spl_rdatum; void* spl_ldatum; } ;
struct TYPE_21__ {int n; TYPE_1__* vector; } ;
struct TYPE_17__ {void* key; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int OffsetNumber ;
typedef  TYPE_5__ GistEntryVector ;
typedef  TYPE_6__ GIST_SPLITVEC ;
typedef  TYPE_7__ GBT_VARKEY_R ;
typedef  int /*<<< orphan*/  GBT_VARKEY ;
typedef  int /*<<< orphan*/  FmgrInfo ;

/* Variables and functions */
 scalar_t__ DatumGetPointer (void*) ; 
 size_t FirstOffsetNumber ; 
 int /*<<< orphan*/  Max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int OffsetNumberNext (int) ; 
 void* PointerGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gbt_var_bin_union (void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__ const*,int /*<<< orphan*/ *) ; 
 TYPE_7__ gbt_var_key_readable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gbt_var_leaf2node (int /*<<< orphan*/ *,TYPE_2__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gbt_var_node_cp_len (int /*<<< orphan*/ *,TYPE_2__ const*) ; 
 int /*<<< orphan*/ * gbt_var_node_truncate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__ const*) ; 
 int /*<<< orphan*/  gbt_vsrt_cmp ; 
 int /*<<< orphan*/ ** palloc (int) ; 
 int /*<<< orphan*/  qsort_arg (void*,int,int,int /*<<< orphan*/ ,void*) ; 

GIST_SPLITVEC *
gbt_var_picksplit(const GistEntryVector *entryvec, GIST_SPLITVEC *v,
				  Oid collation, const gbtree_vinfo *tinfo, FmgrInfo *flinfo)
{
	OffsetNumber i,
				maxoff = entryvec->n - 1;
	Vsrt	   *arr;
	int			svcntr = 0,
				nbytes;
	char	   *cur;
	GBT_VARKEY **sv = NULL;
	gbt_vsrt_arg varg;

	arr = (Vsrt *) palloc((maxoff + 1) * sizeof(Vsrt));
	nbytes = (maxoff + 2) * sizeof(OffsetNumber);
	v->spl_left = (OffsetNumber *) palloc(nbytes);
	v->spl_right = (OffsetNumber *) palloc(nbytes);
	v->spl_ldatum = PointerGetDatum(0);
	v->spl_rdatum = PointerGetDatum(0);
	v->spl_nleft = 0;
	v->spl_nright = 0;

	sv = palloc(sizeof(bytea *) * (maxoff + 1));

	/* Sort entries */

	for (i = FirstOffsetNumber; i <= maxoff; i = OffsetNumberNext(i))
	{
		GBT_VARKEY_R ro;

		cur = (char *) DatumGetPointer(entryvec->vector[i].key);
		ro = gbt_var_key_readable((GBT_VARKEY *) cur);
		if (ro.lower == ro.upper)	/* leaf */
		{
			sv[svcntr] = gbt_var_leaf2node((GBT_VARKEY *) cur, tinfo, flinfo);
			arr[i].t = sv[svcntr];
			if (sv[svcntr] != (GBT_VARKEY *) cur)
				svcntr++;
		}
		else
			arr[i].t = (GBT_VARKEY *) cur;
		arr[i].i = i;
	}

	/* sort */
	varg.tinfo = tinfo;
	varg.collation = collation;
	varg.flinfo = flinfo;
	qsort_arg((void *) &arr[FirstOffsetNumber],
			  maxoff - FirstOffsetNumber + 1,
			  sizeof(Vsrt),
			  gbt_vsrt_cmp,
			  (void *) &varg);

	/* We do simply create two parts */

	for (i = FirstOffsetNumber; i <= maxoff; i = OffsetNumberNext(i))
	{
		if (i <= (maxoff - FirstOffsetNumber + 1) / 2)
		{
			gbt_var_bin_union(&v->spl_ldatum, arr[i].t, collation, tinfo, flinfo);
			v->spl_left[v->spl_nleft] = arr[i].i;
			v->spl_nleft++;
		}
		else
		{
			gbt_var_bin_union(&v->spl_rdatum, arr[i].t, collation, tinfo, flinfo);
			v->spl_right[v->spl_nright] = arr[i].i;
			v->spl_nright++;
		}
	}

	/* Truncate (=compress) key */
	if (tinfo->trnc)
	{
		int32		ll = gbt_var_node_cp_len((GBT_VARKEY *) DatumGetPointer(v->spl_ldatum), tinfo);
		int32		lr = gbt_var_node_cp_len((GBT_VARKEY *) DatumGetPointer(v->spl_rdatum), tinfo);
		GBT_VARKEY *dl;
		GBT_VARKEY *dr;

		ll = Max(ll, lr);
		ll++;

		dl = gbt_var_node_truncate((GBT_VARKEY *) DatumGetPointer(v->spl_ldatum), ll, tinfo);
		dr = gbt_var_node_truncate((GBT_VARKEY *) DatumGetPointer(v->spl_rdatum), ll, tinfo);
		v->spl_ldatum = PointerGetDatum(dl);
		v->spl_rdatum = PointerGetDatum(dr);
	}

	return v;
}