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
RTMP_TLS_Free() {
#ifdef USE_MBEDTLS
    mbedtls_ssl_config_free(&RTMP_TLS_ctx->conf);
    mbedtls_ctr_drbg_free(&RTMP_TLS_ctx->ctr_drbg);
    mbedtls_entropy_free(&RTMP_TLS_ctx->entropy);

    if (RTMP_TLS_ctx->cacert) {
        mbedtls_x509_crt_free(RTMP_TLS_ctx->cacert);
        free(RTMP_TLS_ctx->cacert);
        RTMP_TLS_ctx->cacert = NULL;
    }

    // NO mbedtls_net_free() BECAUSE WE SET IT UP BY HAND!
    free(RTMP_TLS_ctx);
    RTMP_TLS_ctx = NULL;
#endif
}