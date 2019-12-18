#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * search_path; void* right_arg; void* left_arg; int /*<<< orphan*/  oprname; } ;
typedef  int /*<<< orphan*/  ParseState ;
typedef  int /*<<< orphan*/  ParseCallbackState ;
typedef  TYPE_1__ OprCacheKey ;
typedef  void* Oid ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  DeconstructQualifiedName (int /*<<< orphan*/ *,char**,char**) ; 
 int /*<<< orphan*/  LookupExplicitNamespace (char*,int) ; 
 scalar_t__ MAX_CACHED_PATH_LEN ; 
 int /*<<< orphan*/  MemSet (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NAMEDATALEN ; 
 int /*<<< orphan*/  cancel_parser_errposition_callback (int /*<<< orphan*/ *) ; 
 scalar_t__ fetch_search_path_array (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  setup_parser_errposition_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
make_oper_cache_key(ParseState *pstate, OprCacheKey *key, List *opname,
					Oid ltypeId, Oid rtypeId, int location)
{
	char	   *schemaname;
	char	   *opername;

	/* deconstruct the name list */
	DeconstructQualifiedName(opname, &schemaname, &opername);

	/* ensure zero-fill for stable hashing */
	MemSet(key, 0, sizeof(OprCacheKey));

	/* save operator name and input types into key */
	strlcpy(key->oprname, opername, NAMEDATALEN);
	key->left_arg = ltypeId;
	key->right_arg = rtypeId;

	if (schemaname)
	{
		ParseCallbackState pcbstate;

		/* search only in exact schema given */
		setup_parser_errposition_callback(&pcbstate, pstate, location);
		key->search_path[0] = LookupExplicitNamespace(schemaname, false);
		cancel_parser_errposition_callback(&pcbstate);
	}
	else
	{
		/* get the active search path */
		if (fetch_search_path_array(key->search_path,
									MAX_CACHED_PATH_LEN) > MAX_CACHED_PATH_LEN)
			return false;		/* oops, didn't fit */
	}

	return true;
}