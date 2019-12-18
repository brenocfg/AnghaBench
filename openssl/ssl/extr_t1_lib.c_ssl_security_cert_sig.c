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
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int EXFLAG_SS ; 
 int NID_undef ; 
 int X509_get_extension_flags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_get_signature_info (int /*<<< orphan*/ *,int*,int*,int*,int /*<<< orphan*/ *) ; 
 int ssl_ctx_security (int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ *) ; 
 int ssl_security (int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ssl_security_cert_sig(SSL *s, SSL_CTX *ctx, X509 *x, int op)
{
    /* Lookup signature algorithm digest */
    int secbits, nid, pknid;
    /* Don't check signature if self signed */
    if ((X509_get_extension_flags(x) & EXFLAG_SS) != 0)
        return 1;
    if (!X509_get_signature_info(x, &nid, &pknid, &secbits, NULL))
        secbits = -1;
    /* If digest NID not defined use signature NID */
    if (nid == NID_undef)
        nid = pknid;
    if (s)
        return ssl_security(s, op, secbits, nid, x);
    else
        return ssl_ctx_security(ctx, op, secbits, nid, x);
}