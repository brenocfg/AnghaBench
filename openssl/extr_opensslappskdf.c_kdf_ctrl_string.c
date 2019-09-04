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
typedef  int /*<<< orphan*/  EVP_KDF_CTX ;

/* Variables and functions */
 int EVP_KDF_ctrl_str (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 char* OPENSSL_strdup (char const*) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static int kdf_ctrl_string(EVP_KDF_CTX *ctx, const char *value)
{
    int rv;
    char *stmp, *vtmp = NULL;

    stmp = OPENSSL_strdup(value);
    if (stmp == NULL)
        return -1;
    vtmp = strchr(stmp, ':');
    if (vtmp != NULL) {
        *vtmp = 0;
        vtmp++;
    }
    rv = EVP_KDF_ctrl_str(ctx, stmp, vtmp);
    OPENSSL_free(stmp);
    return rv;
}