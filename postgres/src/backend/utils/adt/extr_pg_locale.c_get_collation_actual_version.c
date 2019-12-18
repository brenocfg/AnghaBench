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
typedef  int /*<<< orphan*/  UVersionInfo ;
typedef  int /*<<< orphan*/  UErrorCode ;
typedef  int /*<<< orphan*/  UCollator ;

/* Variables and functions */
 char COLLPROVIDER_ICU ; 
 char COLLPROVIDER_LIBC ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ U_FAILURE (int /*<<< orphan*/ ) ; 
 int U_MAX_VERSION_STRING_LENGTH ; 
 int /*<<< orphan*/  U_ZERO_ERROR ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*,int /*<<< orphan*/ ) ; 
 char* gnu_get_libc_version () ; 
 char* pstrdup (char*) ; 
 int /*<<< orphan*/  u_errorName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u_versionToString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ucol_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucol_getVersion (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ucol_open (char const*,int /*<<< orphan*/ *) ; 

char *
get_collation_actual_version(char collprovider, const char *collcollate)
{
	char	   *collversion = NULL;

#ifdef USE_ICU
	if (collprovider == COLLPROVIDER_ICU)
	{
		UCollator  *collator;
		UErrorCode	status;
		UVersionInfo versioninfo;
		char		buf[U_MAX_VERSION_STRING_LENGTH];

		status = U_ZERO_ERROR;
		collator = ucol_open(collcollate, &status);
		if (U_FAILURE(status))
			ereport(ERROR,
					(errmsg("could not open collator for locale \"%s\": %s",
							collcollate, u_errorName(status))));
		ucol_getVersion(collator, versioninfo);
		ucol_close(collator);

		u_versionToString(versioninfo, buf);
		collversion = pstrdup(buf);
	}
	else
#endif
	if (collprovider == COLLPROVIDER_LIBC)
	{
#if defined(__GLIBC__)
		/* Use the glibc version because we don't have anything better. */
		collversion = pstrdup(gnu_get_libc_version());
#endif
	}

	return collversion;
}