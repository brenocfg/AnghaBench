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
typedef  int DBState ;

/* Variables and functions */
#define  DB_IN_ARCHIVE_RECOVERY 134 
#define  DB_IN_CRASH_RECOVERY 133 
#define  DB_IN_PRODUCTION 132 
#define  DB_SHUTDOWNED 131 
#define  DB_SHUTDOWNED_IN_RECOVERY 130 
#define  DB_SHUTDOWNING 129 
#define  DB_STARTUP 128 
 char const* _ (char*) ; 

__attribute__((used)) static const char *
dbState(DBState state)
{
	switch (state)
	{
		case DB_STARTUP:
			return _("starting up");
		case DB_SHUTDOWNED:
			return _("shut down");
		case DB_SHUTDOWNED_IN_RECOVERY:
			return _("shut down in recovery");
		case DB_SHUTDOWNING:
			return _("shutting down");
		case DB_IN_CRASH_RECOVERY:
			return _("in crash recovery");
		case DB_IN_ARCHIVE_RECOVERY:
			return _("in archive recovery");
		case DB_IN_PRODUCTION:
			return _("in production");
	}
	return _("unrecognized status code");
}