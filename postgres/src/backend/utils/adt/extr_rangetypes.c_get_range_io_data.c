#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int16 ;
struct TYPE_12__ {scalar_t__ type_id; TYPE_1__* rngelemtype; } ;
struct TYPE_11__ {TYPE_2__* flinfo; } ;
struct TYPE_10__ {int /*<<< orphan*/  proc; int /*<<< orphan*/  typiofunc; TYPE_5__* typcache; int /*<<< orphan*/  typioparam; } ;
struct TYPE_9__ {void* fn_extra; int /*<<< orphan*/  fn_mcxt; } ;
struct TYPE_8__ {int /*<<< orphan*/  type_id; } ;
typedef  TYPE_3__ RangeIOData ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  IOFuncSelector ;
typedef  TYPE_4__* FunctionCallInfo ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_UNDEFINED_FUNCTION ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  IOFunc_receive ; 
 scalar_t__ MemoryContextAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPECACHE_RANGE_INFO ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmgr_info_cxt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_type_be (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_type_io_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_5__* lookup_type_cache (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static RangeIOData *
get_range_io_data(FunctionCallInfo fcinfo, Oid rngtypid, IOFuncSelector func)
{
	RangeIOData *cache = (RangeIOData *) fcinfo->flinfo->fn_extra;

	if (cache == NULL || cache->typcache->type_id != rngtypid)
	{
		int16		typlen;
		bool		typbyval;
		char		typalign;
		char		typdelim;

		cache = (RangeIOData *) MemoryContextAlloc(fcinfo->flinfo->fn_mcxt,
												   sizeof(RangeIOData));
		cache->typcache = lookup_type_cache(rngtypid, TYPECACHE_RANGE_INFO);
		if (cache->typcache->rngelemtype == NULL)
			elog(ERROR, "type %u is not a range type", rngtypid);

		/* get_type_io_data does more than we need, but is convenient */
		get_type_io_data(cache->typcache->rngelemtype->type_id,
						 func,
						 &typlen,
						 &typbyval,
						 &typalign,
						 &typdelim,
						 &cache->typioparam,
						 &cache->typiofunc);

		if (!OidIsValid(cache->typiofunc))
		{
			/* this could only happen for receive or send */
			if (func == IOFunc_receive)
				ereport(ERROR,
						(errcode(ERRCODE_UNDEFINED_FUNCTION),
						 errmsg("no binary input function available for type %s",
								format_type_be(cache->typcache->rngelemtype->type_id))));
			else
				ereport(ERROR,
						(errcode(ERRCODE_UNDEFINED_FUNCTION),
						 errmsg("no binary output function available for type %s",
								format_type_be(cache->typcache->rngelemtype->type_id))));
		}
		fmgr_info_cxt(cache->typiofunc, &cache->proc,
					  fcinfo->flinfo->fn_mcxt);

		fcinfo->flinfo->fn_extra = (void *) cache;
	}

	return cache;
}