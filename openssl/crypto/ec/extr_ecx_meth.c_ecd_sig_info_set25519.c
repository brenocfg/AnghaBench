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
typedef  int /*<<< orphan*/  X509_SIG_INFO ;
typedef  int /*<<< orphan*/  X509_ALGOR ;
typedef  int /*<<< orphan*/  ASN1_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  NID_ED25519 ; 
 int /*<<< orphan*/  NID_undef ; 
 int /*<<< orphan*/  X25519_SECURITY_BITS ; 
 int /*<<< orphan*/  X509_SIG_INFO_TLS ; 
 int /*<<< orphan*/  X509_SIG_INFO_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ecd_sig_info_set25519(X509_SIG_INFO *siginf, const X509_ALGOR *alg,
                                 const ASN1_STRING *sig)
{
    X509_SIG_INFO_set(siginf, NID_undef, NID_ED25519, X25519_SECURITY_BITS,
                      X509_SIG_INFO_TLS);
    return 1;
}