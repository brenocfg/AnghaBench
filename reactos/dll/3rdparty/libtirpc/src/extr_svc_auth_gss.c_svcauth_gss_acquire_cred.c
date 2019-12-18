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
 int /*<<< orphan*/  GSS_C_ACCEPT ; 
 int /*<<< orphan*/  GSS_C_NULL_OID_SET ; 
 scalar_t__ GSS_S_COMPLETE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _svcauth_gss_creds ; 
 int /*<<< orphan*/  _svcauth_gss_name ; 
 scalar_t__ gss_acquire_cred (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_debug (char*) ; 
 int /*<<< orphan*/  log_status (char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static bool_t
svcauth_gss_acquire_cred(void)
{
	OM_uint32	maj_stat, min_stat;

	log_debug("in svcauth_gss_acquire_cred()");

	maj_stat = gss_acquire_cred(&min_stat, _svcauth_gss_name, 0,
				    GSS_C_NULL_OID_SET, GSS_C_ACCEPT,
				    &_svcauth_gss_creds, NULL, NULL);

	if (maj_stat != GSS_S_COMPLETE) {
		log_status("gss_acquire_cred", maj_stat, min_stat);
		return (FALSE);
	}
	return (TRUE);
}