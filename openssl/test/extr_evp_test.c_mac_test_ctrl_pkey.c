#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* err; } ;
typedef  TYPE_1__ EVP_TEST ;
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;

/* Variables and functions */
 int EVP_PKEY_CTX_ctrl_str (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 char* OPENSSL_strdup (char const*) ; 
 int /*<<< orphan*/  TEST_ptr (char*) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static int mac_test_ctrl_pkey(EVP_TEST *t, EVP_PKEY_CTX *pctx,
                              const char *value)
{
    int rv;
    char *p, *tmpval;

    if (!TEST_ptr(tmpval = OPENSSL_strdup(value)))
        return 0;
    p = strchr(tmpval, ':');
    if (p != NULL)
        *p++ = '\0';
    rv = EVP_PKEY_CTX_ctrl_str(pctx, tmpval, p);
    if (rv == -2)
        t->err = "PKEY_CTRL_INVALID";
    else if (rv <= 0)
        t->err = "PKEY_CTRL_ERROR";
    else
        rv = 1;
    OPENSSL_free(tmpval);
    return rv > 0;
}