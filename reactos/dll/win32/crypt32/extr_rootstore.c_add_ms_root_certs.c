#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  cb; int /*<<< orphan*/  pb; } ;
typedef  int /*<<< orphan*/  HCERTSTORE ;
typedef  size_t DWORD ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  CERT_STORE_ADD_NEW ; 
 int /*<<< orphan*/  CertAddEncodedCertificateToStore (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  WARN (char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_ASN_ENCODING ; 
 TYPE_1__* msRootCerts ; 

__attribute__((used)) static void add_ms_root_certs(HCERTSTORE to)
{
    DWORD i;

    TRACE("\n");

    for (i = 0; i < ARRAY_SIZE(msRootCerts); i++)
        if (!CertAddEncodedCertificateToStore(to, X509_ASN_ENCODING,
         msRootCerts[i].pb, msRootCerts[i].cb, CERT_STORE_ADD_NEW, NULL))
            WARN("adding root cert %d failed: %08x\n", i, GetLastError());
}