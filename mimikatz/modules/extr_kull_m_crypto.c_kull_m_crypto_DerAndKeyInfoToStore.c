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
typedef  scalar_t__ PCRYPT_KEY_PROV_INFO ;
typedef  int /*<<< orphan*/  PCCERT_CONTEXT ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  scalar_t__ LPCVOID ;
typedef  int /*<<< orphan*/  LPCBYTE ;
typedef  int /*<<< orphan*/  HCERTSTORE ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CERT_CLOSE_STORE_FORCE_FLAG ; 
 int /*<<< orphan*/  CERT_KEY_PROV_INFO_PROP_ID ; 
 int /*<<< orphan*/  CERT_STORE_ADD_ALWAYS ; 
 int /*<<< orphan*/  CERT_STORE_ADD_NEW ; 
 int CERT_STORE_OPEN_EXISTING_FLAG ; 
 int /*<<< orphan*/  CERT_STORE_PROV_SYSTEM ; 
 scalar_t__ CertAddEncodedCertificateToStore (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CertCloseStore (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CertFreeCertificateContext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CertOpenStore (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ CertSetCertificateContextProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 int /*<<< orphan*/  X509_ASN_ENCODING ; 

BOOL kull_m_crypto_DerAndKeyInfoToStore(LPCVOID der, DWORD derLen, PCRYPT_KEY_PROV_INFO pInfo, DWORD systemStore, LPCWSTR store, BOOL force)
{
	BOOL status = FALSE;
	HCERTSTORE hTempStore;
	PCCERT_CONTEXT pCertContext;
	if(hTempStore = CertOpenStore(CERT_STORE_PROV_SYSTEM, 0, 0, CERT_STORE_OPEN_EXISTING_FLAG | systemStore, store))
	{
		if(CertAddEncodedCertificateToStore(hTempStore, X509_ASN_ENCODING, (LPCBYTE) der, derLen, force ? CERT_STORE_ADD_ALWAYS : CERT_STORE_ADD_NEW, &pCertContext))
		{
			if(!(status = CertSetCertificateContextProperty(pCertContext, CERT_KEY_PROV_INFO_PROP_ID, 0, (LPCVOID) pInfo)))
				PRINT_ERROR_AUTO(L"CertSetCertificateContextProperty(CERT_KEY_PROV_INFO_PROP_ID)");
			CertFreeCertificateContext(pCertContext);
		}
		else PRINT_ERROR_AUTO(L"CertAddEncodedCertificateToStore");
		CertCloseStore(hTempStore, CERT_CLOSE_STORE_FORCE_FLAG);
	}
	return status;
}