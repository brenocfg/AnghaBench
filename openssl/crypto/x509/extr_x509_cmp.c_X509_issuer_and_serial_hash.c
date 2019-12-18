#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ length; scalar_t__ data; } ;
struct TYPE_6__ {TYPE_1__ serialNumber; int /*<<< orphan*/  issuer; } ;
struct TYPE_7__ {TYPE_2__ cert_info; } ;
typedef  TYPE_3__ X509 ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_DigestFinal_ex (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestUpdate (int /*<<< orphan*/ *,unsigned char*,unsigned long) ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 int /*<<< orphan*/  EVP_md5 () ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 char* X509_NAME_oneline (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned long strlen (char*) ; 

unsigned long X509_issuer_and_serial_hash(X509 *a)
{
    unsigned long ret = 0;
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    unsigned char md[16];
    char *f;

    if (ctx == NULL)
        goto err;
    f = X509_NAME_oneline(a->cert_info.issuer, NULL, 0);
    if (!EVP_DigestInit_ex(ctx, EVP_md5(), NULL))
        goto err;
    if (!EVP_DigestUpdate(ctx, (unsigned char *)f, strlen(f)))
        goto err;
    OPENSSL_free(f);
    if (!EVP_DigestUpdate
        (ctx, (unsigned char *)a->cert_info.serialNumber.data,
         (unsigned long)a->cert_info.serialNumber.length))
        goto err;
    if (!EVP_DigestFinal_ex(ctx, &(md[0]), NULL))
        goto err;
    ret = (((unsigned long)md[0]) | ((unsigned long)md[1] << 8L) |
           ((unsigned long)md[2] << 16L) | ((unsigned long)md[3] << 24L)
        ) & 0xffffffffL;
 err:
    EVP_MD_CTX_free(ctx);
    return ret;
}