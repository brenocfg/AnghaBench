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
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_4__ {int /*<<< orphan*/  cert; } ;
typedef  TYPE_1__ SSL ;

/* Variables and functions */
 int ERR_R_PASSED_NULL_PARAMETER ; 
 int /*<<< orphan*/  SSL_F_SSL_USE_CERTIFICATE ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int) ; 
 int ssl_security_cert (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int ssl_set_cert (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int SSL_use_certificate(SSL *ssl, X509 *x)
{
    int rv;
    if (x == NULL) {
        SSLerr(SSL_F_SSL_USE_CERTIFICATE, ERR_R_PASSED_NULL_PARAMETER);
        return 0;
    }
    rv = ssl_security_cert(ssl, NULL, x, 0, 1);
    if (rv != 1) {
        SSLerr(SSL_F_SSL_USE_CERTIFICATE, rv);
        return 0;
    }

    return ssl_set_cert(ssl->cert, x);
}