#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * stdname; } ;
typedef  TYPE_1__ const SSL_CIPHER ;

/* Variables and functions */
 size_t OSSL_NELEM (TYPE_1__ const**) ; 
 size_t SSL3_NUM_CIPHERS ; 
 size_t SSL3_NUM_SCSVS ; 
 size_t TLS13_NUM_CIPHERS ; 
 TYPE_1__ const* ssl3_ciphers ; 
 TYPE_1__ const* ssl3_scsvs ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ *) ; 
 TYPE_1__ const* tls13_ciphers ; 

const SSL_CIPHER *ssl3_get_cipher_by_std_name(const char *stdname)
{
    SSL_CIPHER *c = NULL, *tbl;
    SSL_CIPHER *alltabs[] = {tls13_ciphers, ssl3_ciphers};
    size_t i, j, tblsize[] = {TLS13_NUM_CIPHERS, SSL3_NUM_CIPHERS};

    /* this is not efficient, necessary to optimize this? */
    for (j = 0; j < OSSL_NELEM(alltabs); j++) {
        for (i = 0, tbl = alltabs[j]; i < tblsize[j]; i++, tbl++) {
            if (tbl->stdname == NULL)
                continue;
            if (strcmp(stdname, tbl->stdname) == 0) {
                c = tbl;
                break;
            }
        }
    }
    if (c == NULL) {
        tbl = ssl3_scsvs;
        for (i = 0; i < SSL3_NUM_SCSVS; i++, tbl++) {
            if (strcmp(stdname, tbl->stdname) == 0) {
                c = tbl;
                break;
            }
        }
    }
    return c;
}