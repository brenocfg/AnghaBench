#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int is_verify; int is_oneshot; struct TYPE_9__* ctx; int /*<<< orphan*/  const* md; } ;
struct TYPE_8__ {int skip; TYPE_2__* data; } ;
typedef  TYPE_1__ EVP_TEST ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  TYPE_2__ DIGESTSIGN_DATA ;

/* Variables and functions */
 TYPE_2__* EVP_MD_CTX_new () ; 
 int /*<<< orphan*/ * EVP_get_digestbyname (char const*) ; 
 scalar_t__ NID_undef ; 
 scalar_t__ OBJ_ln2nid (char const*) ; 
 scalar_t__ OBJ_sn2nid (char const*) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_2__*) ; 
 TYPE_2__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  TEST_ptr (TYPE_2__*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int digestsigver_test_init(EVP_TEST *t, const char *alg, int is_verify,
                                  int is_oneshot)
{
    const EVP_MD *md = NULL;
    DIGESTSIGN_DATA *mdat;

    if (strcmp(alg, "NULL") != 0) {
        if ((md = EVP_get_digestbyname(alg)) == NULL) {
            /* If alg has an OID assume disabled algorithm */
            if (OBJ_sn2nid(alg) != NID_undef || OBJ_ln2nid(alg) != NID_undef) {
                t->skip = 1;
                return 1;
            }
            return 0;
        }
    }
    if (!TEST_ptr(mdat = OPENSSL_zalloc(sizeof(*mdat))))
        return 0;
    mdat->md = md;
    if (!TEST_ptr(mdat->ctx = EVP_MD_CTX_new())) {
        OPENSSL_free(mdat);
        return 0;
    }
    mdat->is_verify = is_verify;
    mdat->is_oneshot = is_oneshot;
    t->data = mdat;
    return 1;
}