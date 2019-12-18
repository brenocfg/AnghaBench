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
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (int*) ; 
 int* OPENSSL_malloc (size_t) ; 
 int /*<<< orphan*/  SSL_F_TLS1_SET_GROUPS ; 
 int /*<<< orphan*/  SSL_R_BAD_LENGTH ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tls1_nid2group_id (int) ; 

int tls1_set_groups(uint16_t **pext, size_t *pextlen,
                    int *groups, size_t ngroups)
{
#if !defined(OPENSSL_NO_EC) || !defined(OPENSSL_NO_DH)
    uint16_t *glist;
    size_t i;
    /*
     * Bitmap of groups included to detect duplicates: two variables are added
     * to detect duplicates as some values are more than 32.
     */
    unsigned long *dup_list = NULL;
    unsigned long dup_list_egrp = 0;
    unsigned long dup_list_dhgrp = 0;

    if (ngroups == 0) {
        SSLerr(SSL_F_TLS1_SET_GROUPS, SSL_R_BAD_LENGTH);
        return 0;
    }
    if ((glist = OPENSSL_malloc(ngroups * sizeof(*glist))) == NULL) {
        SSLerr(SSL_F_TLS1_SET_GROUPS, ERR_R_MALLOC_FAILURE);
        return 0;
    }
    for (i = 0; i < ngroups; i++) {
        unsigned long idmask;
        uint16_t id;
        id = tls1_nid2group_id(groups[i]);
        if ((id & 0x00FF) >= (sizeof(unsigned long) * 8))
            goto err;
        idmask = 1L << (id & 0x00FF);
        dup_list = (id < 0x100) ? &dup_list_egrp : &dup_list_dhgrp;
        if (!id || ((*dup_list) & idmask))
            goto err;
        *dup_list |= idmask;
        glist[i] = id;
    }
    OPENSSL_free(*pext);
    *pext = glist;
    *pextlen = ngroups;
    return 1;
err:
    OPENSSL_free(glist);
    return 0;
#else
    return 0;
#endif /* !defined(OPENSSL_NO_EC) || !defined(OPENSSL_NO_DH) */
}