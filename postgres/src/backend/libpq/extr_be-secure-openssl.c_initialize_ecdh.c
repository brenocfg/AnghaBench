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
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  EC_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  EC_KEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_KEY_new_by_curve_name (int) ; 
 int /*<<< orphan*/  ERRCODE_CONFIG_FILE_ERROR ; 
 int /*<<< orphan*/  FATAL ; 
 int /*<<< orphan*/  LOG ; 
 int OBJ_sn2nid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSLECDHCurve ; 
 int /*<<< orphan*/  SSL_CTX_set_options (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_tmp_ecdh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_OP_SINGLE_ECDH_USE ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 

__attribute__((used)) static bool
initialize_ecdh(SSL_CTX *context, bool isServerStart)
{
#ifndef OPENSSL_NO_ECDH
	EC_KEY	   *ecdh;
	int			nid;

	nid = OBJ_sn2nid(SSLECDHCurve);
	if (!nid)
	{
		ereport(isServerStart ? FATAL : LOG,
				(errcode(ERRCODE_CONFIG_FILE_ERROR),
				 errmsg("ECDH: unrecognized curve name: %s", SSLECDHCurve)));
		return false;
	}

	ecdh = EC_KEY_new_by_curve_name(nid);
	if (!ecdh)
	{
		ereport(isServerStart ? FATAL : LOG,
				(errcode(ERRCODE_CONFIG_FILE_ERROR),
				 errmsg("ECDH: could not create key")));
		return false;
	}

	SSL_CTX_set_options(context, SSL_OP_SINGLE_ECDH_USE);
	SSL_CTX_set_tmp_ecdh(context, ecdh);
	EC_KEY_free(ecdh);
#endif

	return true;
}