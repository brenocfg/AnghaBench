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
typedef  int /*<<< orphan*/  mbedtls_pk_context ;
typedef  scalar_t__ mbedtls_ecp_group_id ;

/* Variables and functions */
 scalar_t__ MBEDTLS_ECP_DP_NONE ; 
 scalar_t__ MBEDTLS_ECP_DP_SECP256R1 ; 
 scalar_t__ atoi (char*) ; 
 scalar_t__ ecp_curve (char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  gen_key (int /*<<< orphan*/ *,int,unsigned int,int,scalar_t__,int) ; 
 int /*<<< orphan*/  mbedtls_pk_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  write_key (int /*<<< orphan*/ *,char*,int) ; 

int dokey(bool rsa, char **arg)
{
	mbedtls_pk_context key;
	unsigned int ksize = 512;
	int exp = 65537;
	char *path = NULL;
	bool pem = true;
	mbedtls_ecp_group_id curve = MBEDTLS_ECP_DP_SECP256R1;

	while (*arg && **arg == '-') {
		if (!strcmp(*arg, "-out") && arg[1]) {
			path = arg[1];
			arg++;
		} else if (!strcmp(*arg, "-3")) {
			exp = 3;
		} else if (!strcmp(*arg, "-der")) {
			pem = false;
		}
		arg++;
	}

	if (*arg && rsa) {
		ksize = (unsigned int)atoi(*arg);
	} else if (*arg) {
		curve = ecp_curve((const char *)*arg);
		if (curve == MBEDTLS_ECP_DP_NONE) {
			fprintf(stderr, "error: invalid curve name: %s\n", *arg);
			return 1;
		}
	}

	gen_key(&key, rsa, ksize, exp, curve, pem);
	write_key(&key, path, pem);

	mbedtls_pk_free(&key);

	return 0;
}