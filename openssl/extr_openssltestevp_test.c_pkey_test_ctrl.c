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
struct TYPE_3__ {char* err; int skip; } ;
typedef  TYPE_1__ EVP_TEST ;
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;

/* Variables and functions */
 int EVP_PKEY_CTX_ctrl_str (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * EVP_get_cipherbynid (int) ; 
 int /*<<< orphan*/ * EVP_get_digestbynid (int) ; 
 int NID_undef ; 
 int OBJ_ln2nid (char*) ; 
 int OBJ_sn2nid (char*) ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 char* OPENSSL_strdup (char const*) ; 
 int /*<<< orphan*/  TEST_ptr (char*) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static int pkey_test_ctrl(EVP_TEST *t, EVP_PKEY_CTX *pctx,
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
    if (rv == -2) {
        t->err = "PKEY_CTRL_INVALID";
        rv = 1;
    } else if (p != NULL && rv <= 0) {
        /* If p has an OID and lookup fails assume disabled algorithm */
        int nid = OBJ_sn2nid(p);

        if (nid == NID_undef)
             nid = OBJ_ln2nid(p);
        if (nid != NID_undef
                && EVP_get_digestbynid(nid) == NULL
                && EVP_get_cipherbynid(nid) == NULL) {
            t->skip = 1;
            rv = 1;
        } else {
            t->err = "PKEY_CTRL_ERROR";
            rv = 1;
        }
    }
    OPENSSL_free(tmpval);
    return rv > 0;
}