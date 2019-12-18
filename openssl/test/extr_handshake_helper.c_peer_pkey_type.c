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
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int NID_undef ; 
 int /*<<< orphan*/ * SSL_get_peer_certificate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_get0_pubkey (int /*<<< orphan*/ *) ; 
 int pkey_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int peer_pkey_type(SSL *s)
{
    X509 *x = SSL_get_peer_certificate(s);

    if (x != NULL) {
        int nid = pkey_type(X509_get0_pubkey(x));

        X509_free(x);
        return nid;
    }
    return NID_undef;
}