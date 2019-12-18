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
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GUC_ACTION_SAVE ; 
 char* GetConfigOption (char const*,int,int) ; 
 int NewGUCNestLevel () ; 
 int /*<<< orphan*/  PGC_S_SESSION ; 
 int /*<<< orphan*/  PGC_USERSET ; 
 char* PQparameterStatus (int /*<<< orphan*/ *,char const*) ; 
 int lengthof (char const* const*) ; 
 int /*<<< orphan*/  set_config_option (char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static int
applyRemoteGucs(PGconn *conn)
{
	static const char *const GUCsAffectingIO[] = {
		"DateStyle",
		"IntervalStyle"
	};

	int			nestlevel = -1;
	int			i;

	for (i = 0; i < lengthof(GUCsAffectingIO); i++)
	{
		const char *gucName = GUCsAffectingIO[i];
		const char *remoteVal = PQparameterStatus(conn, gucName);
		const char *localVal;

		/*
		 * If the remote server is pre-8.4, it won't have IntervalStyle, but
		 * that's okay because its output format won't be ambiguous.  So just
		 * skip the GUC if we don't get a value for it.  (We might eventually
		 * need more complicated logic with remote-version checks here.)
		 */
		if (remoteVal == NULL)
			continue;

		/*
		 * Avoid GUC-setting overhead if the remote and local GUCs already
		 * have the same value.
		 */
		localVal = GetConfigOption(gucName, false, false);
		Assert(localVal != NULL);

		if (strcmp(remoteVal, localVal) == 0)
			continue;

		/* Create new GUC nest level if we didn't already */
		if (nestlevel < 0)
			nestlevel = NewGUCNestLevel();

		/* Apply the option (this will throw error on failure) */
		(void) set_config_option(gucName, remoteVal,
								 PGC_USERSET, PGC_S_SESSION,
								 GUC_ACTION_SAVE, true, 0, false);
	}

	return nestlevel;
}