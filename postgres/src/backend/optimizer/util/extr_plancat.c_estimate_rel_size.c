#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int int32 ;
struct TYPE_8__ {TYPE_1__* rd_rel; } ;
struct TYPE_7__ {int relkind; double relpages; double reltuples; int /*<<< orphan*/  relallvisible; } ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/  ItemIdData ;
typedef  double BlockNumber ;

/* Variables and functions */
 int BLCKSZ ; 
 int MAXALIGN (int /*<<< orphan*/ ) ; 
#define  RELKIND_FOREIGN_TABLE 133 
#define  RELKIND_INDEX 132 
#define  RELKIND_MATVIEW 131 
#define  RELKIND_RELATION 130 
#define  RELKIND_SEQUENCE 129 
#define  RELKIND_TOASTVALUE 128 
 double RelationGetNumberOfBlocks (TYPE_2__*) ; 
 int SizeOfPageHeaderData ; 
 int /*<<< orphan*/  SizeofHeapTupleHeader ; 
 int get_rel_data_width (TYPE_2__*,int*) ; 
 double rint (double) ; 
 int /*<<< orphan*/  table_relation_estimate_size (TYPE_2__*,int*,double*,double*,double*) ; 

void
estimate_rel_size(Relation rel, int32 *attr_widths,
				  BlockNumber *pages, double *tuples, double *allvisfrac)
{
	BlockNumber curpages;
	BlockNumber relpages;
	double		reltuples;
	BlockNumber relallvisible;
	double		density;

	switch (rel->rd_rel->relkind)
	{
		case RELKIND_RELATION:
		case RELKIND_MATVIEW:
		case RELKIND_TOASTVALUE:
			table_relation_estimate_size(rel, attr_widths, pages, tuples,
										 allvisfrac);
			break;

		case RELKIND_INDEX:

			/*
			 * XXX: It'd probably be good to move this into a callback,
			 * individual index types e.g. know if they have a metapage.
			 */

			/* it has storage, ok to call the smgr */
			curpages = RelationGetNumberOfBlocks(rel);

			/* coerce values in pg_class to more desirable types */
			relpages = (BlockNumber) rel->rd_rel->relpages;
			reltuples = (double) rel->rd_rel->reltuples;
			relallvisible = (BlockNumber) rel->rd_rel->relallvisible;

			/* report estimated # pages */
			*pages = curpages;
			/* quick exit if rel is clearly empty */
			if (curpages == 0)
			{
				*tuples = 0;
				*allvisfrac = 0;
				break;
			}
			/* coerce values in pg_class to more desirable types */
			relpages = (BlockNumber) rel->rd_rel->relpages;
			reltuples = (double) rel->rd_rel->reltuples;
			relallvisible = (BlockNumber) rel->rd_rel->relallvisible;

			/*
			 * Discount the metapage while estimating the number of tuples.
			 * This is a kluge because it assumes more than it ought to about
			 * index structure.  Currently it's OK for btree, hash, and GIN
			 * indexes but suspect for GiST indexes.
			 */
			if (relpages > 0)
			{
				curpages--;
				relpages--;
			}

			/* estimate number of tuples from previous tuple density */
			if (relpages > 0)
				density = reltuples / (double) relpages;
			else
			{
				/*
				 * When we have no data because the relation was truncated,
				 * estimate tuple width from attribute datatypes.  We assume
				 * here that the pages are completely full, which is OK for
				 * tables (since they've presumably not been VACUUMed yet) but
				 * is probably an overestimate for indexes.  Fortunately
				 * get_relation_info() can clamp the overestimate to the
				 * parent table's size.
				 *
				 * Note: this code intentionally disregards alignment
				 * considerations, because (a) that would be gilding the lily
				 * considering how crude the estimate is, and (b) it creates
				 * platform dependencies in the default plans which are kind
				 * of a headache for regression testing.
				 *
				 * XXX: Should this logic be more index specific?
				 */
				int32		tuple_width;

				tuple_width = get_rel_data_width(rel, attr_widths);
				tuple_width += MAXALIGN(SizeofHeapTupleHeader);
				tuple_width += sizeof(ItemIdData);
				/* note: integer division is intentional here */
				density = (BLCKSZ - SizeOfPageHeaderData) / tuple_width;
			}
			*tuples = rint(density * (double) curpages);

			/*
			 * We use relallvisible as-is, rather than scaling it up like we
			 * do for the pages and tuples counts, on the theory that any
			 * pages added since the last VACUUM are most likely not marked
			 * all-visible.  But costsize.c wants it converted to a fraction.
			 */
			if (relallvisible == 0 || curpages <= 0)
				*allvisfrac = 0;
			else if ((double) relallvisible >= curpages)
				*allvisfrac = 1;
			else
				*allvisfrac = (double) relallvisible / curpages;
			break;

		case RELKIND_SEQUENCE:
			/* Sequences always have a known size */
			*pages = 1;
			*tuples = 1;
			*allvisfrac = 0;
			break;
		case RELKIND_FOREIGN_TABLE:
			/* Just use whatever's in pg_class */
			*pages = rel->rd_rel->relpages;
			*tuples = rel->rd_rel->reltuples;
			*allvisfrac = 0;
			break;
		default:
			/* else it has no disk storage; probably shouldn't get here? */
			*pages = 0;
			*tuples = 0;
			*allvisfrac = 0;
			break;
	}
}