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

/* Variables and functions */
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  show_available_tls_ciphers_list (char const*,char const*,int) ; 

void
show_available_tls_ciphers(const char *cipher_list,
                           const char *cipher_list_tls13,
                           const char *tls_cert_profile)
{
    printf("Available TLS Ciphers, listed in order of preference:\n");

#if (ENABLE_CRYPTO_OPENSSL && OPENSSL_VERSION_NUMBER >= 0x1010100fL)
    printf("\nFor TLS 1.3 and newer (--tls-ciphersuites):\n\n");
    show_available_tls_ciphers_list(cipher_list_tls13, tls_cert_profile, true);
#else
    (void) cipher_list_tls13;  /* Avoid unused warning */
#endif

    printf("\nFor TLS 1.2 and older (--tls-cipher):\n\n");
    show_available_tls_ciphers_list(cipher_list, tls_cert_profile, false);

    printf("\n"
           "Be aware that that whether a cipher suite in this list can actually work\n"
           "depends on the specific setup of both peers. See the man page entries of\n"
           "--tls-cipher and --show-tls for more details.\n\n"
           );
}