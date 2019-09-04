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
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_PKEY_DSA_SIGN ; 
 int /*<<< orphan*/  SSL_PKEY_ECC ; 
 int /*<<< orphan*/  SSL_PKEY_ED25519 ; 
 int /*<<< orphan*/  SSL_PKEY_ED448 ; 
 int /*<<< orphan*/  SSL_PKEY_GOST01 ; 
 int /*<<< orphan*/  SSL_PKEY_GOST12_256 ; 
 int /*<<< orphan*/  SSL_PKEY_GOST12_512 ; 
 int /*<<< orphan*/  SSL_PKEY_RSA ; 
 int /*<<< orphan*/  SSL_PKEY_RSA_PSS_SIGN ; 
 int /*<<< orphan*/  tls1_check_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void tls1_set_cert_validity(SSL *s)
{
    tls1_check_chain(s, NULL, NULL, NULL, SSL_PKEY_RSA);
    tls1_check_chain(s, NULL, NULL, NULL, SSL_PKEY_RSA_PSS_SIGN);
    tls1_check_chain(s, NULL, NULL, NULL, SSL_PKEY_DSA_SIGN);
    tls1_check_chain(s, NULL, NULL, NULL, SSL_PKEY_ECC);
    tls1_check_chain(s, NULL, NULL, NULL, SSL_PKEY_GOST01);
    tls1_check_chain(s, NULL, NULL, NULL, SSL_PKEY_GOST12_256);
    tls1_check_chain(s, NULL, NULL, NULL, SSL_PKEY_GOST12_512);
    tls1_check_chain(s, NULL, NULL, NULL, SSL_PKEY_ED25519);
    tls1_check_chain(s, NULL, NULL, NULL, SSL_PKEY_ED448);
}