#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ version; int sig_len; int /*<<< orphan*/  sig; int /*<<< orphan*/  sig_alg; int /*<<< orphan*/  hash_alg; } ;
typedef  TYPE_1__ SCT ;

/* Variables and functions */
 int /*<<< orphan*/  CT_F_I2O_SCT_SIGNATURE ; 
 int /*<<< orphan*/  CT_R_SCT_INVALID_SIGNATURE ; 
 int /*<<< orphan*/  CT_R_UNSUPPORTED_VERSION ; 
 int /*<<< orphan*/  CTerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (size_t) ; 
 scalar_t__ SCT_VERSION_V1 ; 
 int /*<<< orphan*/  SCT_signature_is_complete (TYPE_1__ const*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s2n (int,unsigned char*) ; 

int i2o_SCT_signature(const SCT *sct, unsigned char **out)
{
    size_t len;
    unsigned char *p = NULL, *pstart = NULL;

    if (!SCT_signature_is_complete(sct)) {
        CTerr(CT_F_I2O_SCT_SIGNATURE, CT_R_SCT_INVALID_SIGNATURE);
        goto err;
    }

    if (sct->version != SCT_VERSION_V1) {
        CTerr(CT_F_I2O_SCT_SIGNATURE, CT_R_UNSUPPORTED_VERSION);
        goto err;
    }

    /*
    * (1 byte) Hash algorithm
    * (1 byte) Signature algorithm
    * (2 bytes + ?) Signature
    */
    len = 4 + sct->sig_len;

    if (out != NULL) {
        if (*out != NULL) {
            p = *out;
            *out += len;
        } else {
            pstart = p = OPENSSL_malloc(len);
            if (p == NULL) {
                CTerr(CT_F_I2O_SCT_SIGNATURE, ERR_R_MALLOC_FAILURE);
                goto err;
            }
            *out = p;
        }

        *p++ = sct->hash_alg;
        *p++ = sct->sig_alg;
        s2n(sct->sig_len, p);
        memcpy(p, sct->sig, sct->sig_len);
    }

    return len;
err:
    OPENSSL_free(pstart);
    return -1;
}