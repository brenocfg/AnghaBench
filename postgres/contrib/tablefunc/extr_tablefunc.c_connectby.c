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
typedef  int /*<<< orphan*/  Tuplestorestate ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  AttInMetadata ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int SPI_connect () ; 
 int /*<<< orphan*/  SPI_finish () ; 
 int /*<<< orphan*/  build_tuplestore_recursively (char*,char*,char*,char*,char*,char*,char*,int /*<<< orphan*/ ,int*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * tuplestore_begin_heap (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  work_mem ; 

__attribute__((used)) static Tuplestorestate *
connectby(char *relname,
		  char *key_fld,
		  char *parent_key_fld,
		  char *orderby_fld,
		  char *branch_delim,
		  char *start_with,
		  int max_depth,
		  bool show_branch,
		  bool show_serial,
		  MemoryContext per_query_ctx,
		  bool randomAccess,
		  AttInMetadata *attinmeta)
{
	Tuplestorestate *tupstore = NULL;
	int			ret;
	MemoryContext oldcontext;

	int			serial = 1;

	/* Connect to SPI manager */
	if ((ret = SPI_connect()) < 0)
		/* internal error */
		elog(ERROR, "connectby: SPI_connect returned %d", ret);

	/* switch to longer term context to create the tuple store */
	oldcontext = MemoryContextSwitchTo(per_query_ctx);

	/* initialize our tuplestore */
	tupstore = tuplestore_begin_heap(randomAccess, false, work_mem);

	MemoryContextSwitchTo(oldcontext);

	/* now go get the whole tree */
	build_tuplestore_recursively(key_fld,
								 parent_key_fld,
								 relname,
								 orderby_fld,
								 branch_delim,
								 start_with,
								 start_with,	/* current_branch */
								 0, /* initial level is 0 */
								 &serial,	/* initial serial is 1 */
								 max_depth,
								 show_branch,
								 show_serial,
								 per_query_ctx,
								 attinmeta,
								 tupstore);

	SPI_finish();

	return tupstore;
}