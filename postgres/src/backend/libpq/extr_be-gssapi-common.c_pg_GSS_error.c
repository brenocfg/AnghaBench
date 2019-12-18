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
typedef  int /*<<< orphan*/  msg_minor ;
typedef  int /*<<< orphan*/  msg_major ;
typedef  int /*<<< orphan*/  OM_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  GSS_C_GSS_CODE ; 
 int /*<<< orphan*/  GSS_C_MECH_CODE ; 
 int /*<<< orphan*/  ereport (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail_internal (char*,char*,char*) ; 
 int /*<<< orphan*/  errmsg_internal (char*,char const*) ; 
 int /*<<< orphan*/  pg_GSS_error_int (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
pg_GSS_error(int severity, const char *errmsg,
			 OM_uint32 maj_stat, OM_uint32 min_stat)
{
	char		msg_major[128],
				msg_minor[128];

	/* Fetch major status message */
	pg_GSS_error_int(msg_major, sizeof(msg_major), maj_stat, GSS_C_GSS_CODE);

	/* Fetch mechanism minor status message */
	pg_GSS_error_int(msg_minor, sizeof(msg_minor), min_stat, GSS_C_MECH_CODE);

	/*
	 * errmsg_internal, since translation of the first part must be done
	 * before calling this function anyway.
	 */
	ereport(severity,
			(errmsg_internal("%s", errmsg),
			 errdetail_internal("%s: %s", msg_major, msg_minor)));
}