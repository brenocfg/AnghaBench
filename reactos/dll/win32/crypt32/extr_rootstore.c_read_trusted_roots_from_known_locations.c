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
typedef  int /*<<< orphan*/  SecCertificateRef ;
typedef  scalar_t__ OSStatus ;
typedef  scalar_t__ HCERTSTORE ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  CFDataRef ;
typedef  int /*<<< orphan*/  CFArrayRef ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CERT_STORE_ADD_NEW ; 
 int /*<<< orphan*/  CERT_STORE_CREATE_NEW_FLAG ; 
 int /*<<< orphan*/  CERT_STORE_PROV_MEMORY ; 
 int CFArrayGetCount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFArrayGetValueAtIndex (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CFDataGetBytePtr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFDataGetLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CRYPT_knownLocations ; 
 scalar_t__ CertAddEncodedCertificateToStore (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CertCloseStore (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ CertOpenStore (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ FALSE ; 
 unsigned int GetLastError () ; 
 scalar_t__ SecKeychainItemExport (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ SecTrustCopyAnchorCertificates (int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WARN (char*,int,unsigned int) ; 
 int /*<<< orphan*/  X509_ASN_ENCODING ; 
 int /*<<< orphan*/  check_and_store_certs (scalar_t__,scalar_t__) ; 
 scalar_t__ import_certs_from_path (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  kSecFormatX509Cert ; 
 scalar_t__ noErr ; 

__attribute__((used)) static void read_trusted_roots_from_known_locations(HCERTSTORE store)
{
    HCERTSTORE from = CertOpenStore(CERT_STORE_PROV_MEMORY,
     X509_ASN_ENCODING, 0, CERT_STORE_CREATE_NEW_FLAG, NULL);

    if (from)
    {
        DWORD i;
        BOOL ret = FALSE;

#ifdef HAVE_SECURITY_SECURITY_H
        OSStatus status;
        CFArrayRef rootCerts;

        status = SecTrustCopyAnchorCertificates(&rootCerts);
        if (status == noErr)
        {
            int i;
            for (i = 0; i < CFArrayGetCount(rootCerts); i++)
            {
                SecCertificateRef cert = (SecCertificateRef)CFArrayGetValueAtIndex(rootCerts, i);
                CFDataRef certData;
                if ((status = SecKeychainItemExport(cert, kSecFormatX509Cert, 0, NULL, &certData)) == noErr)
                {
                    if (CertAddEncodedCertificateToStore(store, X509_ASN_ENCODING,
                            CFDataGetBytePtr(certData), CFDataGetLength(certData),
                            CERT_STORE_ADD_NEW, NULL))
                        ret = TRUE;
                    else
                        WARN("adding root cert %d failed: %08x\n", i, GetLastError());
                    CFRelease(certData);
                }
                else
                    WARN("could not export certificate %d to X509 format: 0x%08x\n", i, (unsigned int)status);
            }
            CFRelease(rootCerts);
        }
#endif

        for (i = 0; !ret && i < ARRAY_SIZE(CRYPT_knownLocations); i++)
            ret = import_certs_from_path(CRYPT_knownLocations[i], from, TRUE);
        check_and_store_certs(from, store);
    }
    CertCloseStore(from, 0);
}