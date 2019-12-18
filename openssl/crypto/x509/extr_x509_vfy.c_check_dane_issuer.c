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
struct TYPE_4__ {int num_untrusted; int /*<<< orphan*/  chain; int /*<<< orphan*/ * dane; } ;
typedef  TYPE_1__ X509_STORE_CTX ;
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  SSL_DANE ;

/* Variables and functions */
 int /*<<< orphan*/  DANETLS_HAS_TA (int /*<<< orphan*/ *) ; 
 int X509_TRUST_REJECTED ; 
 int X509_TRUST_TRUSTED ; 
 int X509_TRUST_UNTRUSTED ; 
 int dane_match (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * sk_X509_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int check_dane_issuer(X509_STORE_CTX *ctx, int depth)
{
    SSL_DANE *dane = ctx->dane;
    int matched = 0;
    X509 *cert;

    if (!DANETLS_HAS_TA(dane) || depth == 0)
        return  X509_TRUST_UNTRUSTED;

    /*
     * Record any DANE trust-anchor matches, for the first depth to test, if
     * there's one at that depth. (This'll be false for length 1 chains looking
     * for an exact match for the leaf certificate).
     */
    cert = sk_X509_value(ctx->chain, depth);
    if (cert != NULL && (matched = dane_match(ctx, cert, depth)) < 0)
        return  X509_TRUST_REJECTED;
    if (matched > 0) {
        ctx->num_untrusted = depth - 1;
        return  X509_TRUST_TRUSTED;
    }

    return  X509_TRUST_UNTRUSTED;
}