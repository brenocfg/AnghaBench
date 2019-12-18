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
typedef  int /*<<< orphan*/ * gss_cred_id_t ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  GSS_C_INITIATE ; 
 int /*<<< orphan*/ * GSS_C_NO_CREDENTIAL ; 
 int /*<<< orphan*/  GSS_C_NO_NAME ; 
 int /*<<< orphan*/  GSS_C_NO_OID_SET ; 
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ gss_acquire_cred (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool
pg_GSS_have_cred_cache(gss_cred_id_t *cred_out)
{
	OM_uint32	major,
				minor;
	gss_cred_id_t cred = GSS_C_NO_CREDENTIAL;

	major = gss_acquire_cred(&minor, GSS_C_NO_NAME, 0, GSS_C_NO_OID_SET,
							 GSS_C_INITIATE, &cred, NULL, NULL);
	if (major != GSS_S_COMPLETE)
	{
		*cred_out = NULL;
		return false;
	}
	*cred_out = cred;
	return true;
}