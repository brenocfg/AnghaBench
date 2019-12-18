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

/* Variables and functions */
 int /*<<< orphan*/  GetConfigOption (char const*,int,int) ; 
#define  PG_TLS1_1_VERSION 132 
#define  PG_TLS1_2_VERSION 131 
#define  PG_TLS1_3_VERSION 130 
#define  PG_TLS1_VERSION 129 
#define  PG_TLS_ANY 128 
 int TLS1_1_VERSION ; 
 int TLS1_2_VERSION ; 
 int TLS1_3_VERSION ; 
 int TLS1_VERSION ; 
 int /*<<< orphan*/  ereport (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ssl_protocol_version_to_openssl(int v, const char *guc_name, int loglevel)
{
	switch (v)
	{
		case PG_TLS_ANY:
			return 0;
		case PG_TLS1_VERSION:
			return TLS1_VERSION;
		case PG_TLS1_1_VERSION:
#ifdef TLS1_1_VERSION
			return TLS1_1_VERSION;
#else
			break;
#endif
		case PG_TLS1_2_VERSION:
#ifdef TLS1_2_VERSION
			return TLS1_2_VERSION;
#else
			break;
#endif
		case PG_TLS1_3_VERSION:
#ifdef TLS1_3_VERSION
			return TLS1_3_VERSION;
#else
			break;
#endif
	}

	ereport(loglevel,
			(errmsg("%s setting %s not supported by this build",
					guc_name,
					GetConfigOption(guc_name, false, false))));
	return -1;
}