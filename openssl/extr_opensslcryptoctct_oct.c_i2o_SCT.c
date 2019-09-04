#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int ext_len; int sig_len; size_t sct_len; int /*<<< orphan*/  sct; int /*<<< orphan*/  ext; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  log_id; int /*<<< orphan*/  version; } ;
typedef  TYPE_1__ SCT ;

/* Variables and functions */
 int /*<<< orphan*/  CT_F_I2O_SCT ; 
 int /*<<< orphan*/  CT_R_SCT_NOT_SET ; 
 size_t CT_V1_HASHLEN ; 
 int /*<<< orphan*/  CTerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (size_t) ; 
 int /*<<< orphan*/  SCT_VERSION_V1 ; 
 int /*<<< orphan*/  SCT_is_complete (TYPE_1__ const*) ; 
 scalar_t__ i2o_SCT_signature (TYPE_1__ const*,unsigned char**) ; 
 int /*<<< orphan*/  l2n8 (int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  s2n (int,unsigned char*) ; 

int i2o_SCT(const SCT *sct, unsigned char **out)
{
    size_t len;
    unsigned char *p = NULL, *pstart = NULL;

    if (!SCT_is_complete(sct)) {
        CTerr(CT_F_I2O_SCT, CT_R_SCT_NOT_SET);
        goto err;
    }
    /*
     * Fixed-length header: struct { (1 byte) Version sct_version; (32 bytes)
     * log_id id; (8 bytes) uint64 timestamp; (2 bytes + ?) CtExtensions
     * extensions; (1 byte) Hash algorithm (1 byte) Signature algorithm (2
     * bytes + ?) Signature
     */
    if (sct->version == SCT_VERSION_V1)
        len = 43 + sct->ext_len + 4 + sct->sig_len;
    else
        len = sct->sct_len;

    if (out == NULL)
        return len;

    if (*out != NULL) {
        p = *out;
        *out += len;
    } else {
        pstart = p = OPENSSL_malloc(len);
        if (p == NULL) {
            CTerr(CT_F_I2O_SCT, ERR_R_MALLOC_FAILURE);
            goto err;
        }
        *out = p;
    }

    if (sct->version == SCT_VERSION_V1) {
        *p++ = sct->version;
        memcpy(p, sct->log_id, CT_V1_HASHLEN);
        p += CT_V1_HASHLEN;
        l2n8(sct->timestamp, p);
        s2n(sct->ext_len, p);
        if (sct->ext_len > 0) {
            memcpy(p, sct->ext, sct->ext_len);
            p += sct->ext_len;
        }
        if (i2o_SCT_signature(sct, &p) <= 0)
            goto err;
    } else {
        memcpy(p, sct->sct, len);
    }

    return len;
err:
    OPENSSL_free(pstart);
    return -1;
}