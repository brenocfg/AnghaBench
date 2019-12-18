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
struct TYPE_7__ {TYPE_2__* cert; } ;
struct TYPE_6__ {TYPE_1__* key; } ;
struct TYPE_5__ {int /*<<< orphan*/ * privatekey; int /*<<< orphan*/ * x509; } ;
typedef  TYPE_3__ SSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_F_SSL_CTX_CHECK_PRIVATE_KEY ; 
 int /*<<< orphan*/  SSL_R_NO_CERTIFICATE_ASSIGNED ; 
 int /*<<< orphan*/  SSL_R_NO_PRIVATE_KEY_ASSIGNED ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int X509_check_private_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int SSL_CTX_check_private_key(const SSL_CTX *ctx)
{
    if ((ctx == NULL) || (ctx->cert->key->x509 == NULL)) {
        SSLerr(SSL_F_SSL_CTX_CHECK_PRIVATE_KEY, SSL_R_NO_CERTIFICATE_ASSIGNED);
        return 0;
    }
    if (ctx->cert->key->privatekey == NULL) {
        SSLerr(SSL_F_SSL_CTX_CHECK_PRIVATE_KEY, SSL_R_NO_PRIVATE_KEY_ASSIGNED);
        return 0;
    }
    return X509_check_private_key
            (ctx->cert->key->x509, ctx->cert->key->privatekey);
}