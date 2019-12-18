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
typedef  int /*<<< orphan*/  int16 ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int IndexAMProperty ;

/* Variables and functions */
 int /*<<< orphan*/  AMPROCNUM ; 
#define  AMPROP_DISTANCE_ORDERABLE 129 
#define  AMPROP_RETURNABLE 128 
 int /*<<< orphan*/  GIST_COMPRESS_PROC ; 
 int /*<<< orphan*/  GIST_DISTANCE_PROC ; 
 int /*<<< orphan*/  GIST_FETCH_PROC ; 
 int /*<<< orphan*/  Int16GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int SearchSysCacheExists4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_index_column_opclass (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_opclass_opfamily_and_input_type (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool
gistproperty(Oid index_oid, int attno,
			 IndexAMProperty prop, const char *propname,
			 bool *res, bool *isnull)
{
	Oid			opclass,
				opfamily,
				opcintype;
	int16		procno;

	/* Only answer column-level inquiries */
	if (attno == 0)
		return false;

	/*
	 * Currently, GiST distance-ordered scans require that there be a distance
	 * function in the opclass with the default types (i.e. the one loaded
	 * into the relcache entry, see initGISTstate).  So we assume that if such
	 * a function exists, then there's a reason for it (rather than grubbing
	 * through all the opfamily's operators to find an ordered one).
	 *
	 * Essentially the same code can test whether we support returning the
	 * column data, since that's true if the opclass provides a fetch proc.
	 */

	switch (prop)
	{
		case AMPROP_DISTANCE_ORDERABLE:
			procno = GIST_DISTANCE_PROC;
			break;
		case AMPROP_RETURNABLE:
			procno = GIST_FETCH_PROC;
			break;
		default:
			return false;
	}

	/* First we need to know the column's opclass. */
	opclass = get_index_column_opclass(index_oid, attno);
	if (!OidIsValid(opclass))
	{
		*isnull = true;
		return true;
	}

	/* Now look up the opclass family and input datatype. */
	if (!get_opclass_opfamily_and_input_type(opclass, &opfamily, &opcintype))
	{
		*isnull = true;
		return true;
	}

	/* And now we can check whether the function is provided. */

	*res = SearchSysCacheExists4(AMPROCNUM,
								 ObjectIdGetDatum(opfamily),
								 ObjectIdGetDatum(opcintype),
								 ObjectIdGetDatum(opcintype),
								 Int16GetDatum(procno));

	/*
	 * Special case: even without a fetch function, AMPROP_RETURNABLE is true
	 * if the opclass has no compress function.
	 */
	if (prop == AMPROP_RETURNABLE && !*res)
	{
		*res = !SearchSysCacheExists4(AMPROCNUM,
									  ObjectIdGetDatum(opfamily),
									  ObjectIdGetDatum(opcintype),
									  ObjectIdGetDatum(opcintype),
									  Int16GetDatum(GIST_COMPRESS_PROC));
	}

	*isnull = false;

	return true;
}