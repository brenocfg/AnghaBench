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
typedef  int /*<<< orphan*/  bool_t ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GSS_S_COMPLETE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * _svcauth_gss_creds ; 
 scalar_t__ gss_release_cred (scalar_t__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  log_debug (char*) ; 
 int /*<<< orphan*/  log_status (char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static bool_t
svcauth_gss_release_cred(void)
{
	OM_uint32	maj_stat, min_stat;

	log_debug("in svcauth_gss_release_cred()");

	maj_stat = gss_release_cred(&min_stat, &_svcauth_gss_creds);

	if (maj_stat != GSS_S_COMPLETE) {
		log_status("gss_release_cred", maj_stat, min_stat);
		return (FALSE);
	}

	_svcauth_gss_creds = NULL;

	return (TRUE);
}