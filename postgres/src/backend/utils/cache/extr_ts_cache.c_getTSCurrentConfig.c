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
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  InvalidOid ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * TSConfigCacheHash ; 
 char* TSCurrentConfig ; 
 int /*<<< orphan*/  TSCurrentConfigCache ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  get_ts_config_oid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  init_ts_config_cache () ; 
 int /*<<< orphan*/  stringToQualifiedNameList (char*) ; 

Oid
getTSCurrentConfig(bool emitError)
{
	/* if we have a cached value, return it */
	if (OidIsValid(TSCurrentConfigCache))
		return TSCurrentConfigCache;

	/* fail if GUC hasn't been set up yet */
	if (TSCurrentConfig == NULL || *TSCurrentConfig == '\0')
	{
		if (emitError)
			elog(ERROR, "text search configuration isn't set");
		else
			return InvalidOid;
	}

	if (TSConfigCacheHash == NULL)
	{
		/* First time through: initialize the tsconfig inval callback */
		init_ts_config_cache();
	}

	/* Look up the config */
	TSCurrentConfigCache =
		get_ts_config_oid(stringToQualifiedNameList(TSCurrentConfig),
						  !emitError);

	return TSCurrentConfigCache;
}