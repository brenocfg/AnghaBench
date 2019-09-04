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

void
RTMP_TLS_LoadCerts() {
#ifdef USE_MBEDTLS
    mbedtls_x509_crt *chain = RTMP_TLS_ctx->cacert = calloc(1, sizeof(struct mbedtls_x509_crt));
    mbedtls_x509_crt_init(chain);

#if defined(_WIN32)
    HCERTSTORE hCertStore;
    PCCERT_CONTEXT pCertContext = NULL;

    if (!(hCertStore = CertOpenSystemStore((HCRYPTPROV)NULL, L"ROOT"))) {
        goto error;
    }

    while (pCertContext = CertEnumCertificatesInStore(hCertStore, pCertContext)) {
        mbedtls_x509_crt_parse_der(chain,
                                   (unsigned char *)pCertContext->pbCertEncoded,
                                   pCertContext->cbCertEncoded);
    }

    CertFreeCertificateContext(pCertContext);
    CertCloseStore(hCertStore, 0);
#elif defined(__APPLE__)
    SecKeychainRef keychain_ref;
    CFMutableDictionaryRef search_settings_ref;
    CFArrayRef result_ref;

    if (SecKeychainOpen("/System/Library/Keychains/SystemRootCertificates.keychain",
                        &keychain_ref)
        != errSecSuccess) {
      goto error;
    }

    search_settings_ref = CFDictionaryCreateMutable(NULL, 0, NULL, NULL);
    CFDictionarySetValue(search_settings_ref, kSecClass, kSecClassCertificate);
    CFDictionarySetValue(search_settings_ref, kSecMatchLimit, kSecMatchLimitAll);
    CFDictionarySetValue(search_settings_ref, kSecReturnRef, kCFBooleanTrue);
    CFDictionarySetValue(search_settings_ref, kSecMatchSearchList,
                         CFArrayCreate(NULL, (const void **)&keychain_ref, 1, NULL));

    if (SecItemCopyMatching(search_settings_ref, (CFTypeRef *)&result_ref)
        != errSecSuccess) {
      goto error;
    }

    for (CFIndex i = 0; i < CFArrayGetCount(result_ref); i++) {
      SecCertificateRef item_ref = (SecCertificateRef)
                                   CFArrayGetValueAtIndex(result_ref, i);
      CFDataRef data_ref;

      if ((data_ref = SecCertificateCopyData(item_ref))) {
        mbedtls_x509_crt_parse_der(chain,
                                   (unsigned char *)CFDataGetBytePtr(data_ref),
                                   CFDataGetLength(data_ref));
        CFRelease(data_ref);
      }
    }

    CFRelease(keychain_ref);
#elif defined(__linux__)
    if (mbedtls_x509_crt_parse_path(chain, "/etc/ssl/certs/") != 0) {
        goto error;
    }
#endif

    mbedtls_ssl_conf_ca_chain(&RTMP_TLS_ctx->conf, chain, NULL);
    return;

error:
    mbedtls_x509_crt_free(chain);
    free(chain);
    RTMP_TLS_ctx->cacert = NULL;
#endif /* USE_MBEDTLS */
}