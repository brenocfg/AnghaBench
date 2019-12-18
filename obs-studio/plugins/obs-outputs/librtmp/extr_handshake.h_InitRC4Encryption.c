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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  RC4_handle ;
typedef  int /*<<< orphan*/  HMAC_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  HMAC_crunch (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  HMAC_finish (int /*<<< orphan*/ ,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  HMAC_setup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RC4_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RC4_setkey (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RTMP_LOGDEBUG ; 
 int /*<<< orphan*/  RTMP_Log (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RTMP_LogHex (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int SHA256_DIGEST_LENGTH ; 

__attribute__((used)) static void InitRC4Encryption
(uint8_t * secretKey,
 uint8_t * pubKeyIn,
 uint8_t * pubKeyOut, RC4_handle *rc4keyIn, RC4_handle *rc4keyOut)
{
    uint8_t digest[SHA256_DIGEST_LENGTH];
#if !(defined(USE_MBEDTLS) || defined(USE_POLARSSL) || defined(USE_GNUTLS))
    unsigned int digestLen = 0;
#endif
    HMAC_CTX ctx;

    RC4_alloc(rc4keyIn);
    RC4_alloc(rc4keyOut);

    HMAC_setup(ctx, secretKey, 128);
    HMAC_crunch(ctx, pubKeyIn, 128);
#if defined(USE_MBEDTLS) || defined(USE_POLARSSL) || defined(USE_GNUTLS)
    HMAC_finish(ctx, digest);
#else
    HMAC_finish(ctx, digest, digestLen);
#endif

    RTMP_Log(RTMP_LOGDEBUG, "RC4 Out Key: ");
    RTMP_LogHex(RTMP_LOGDEBUG, digest, 16);

    RC4_setkey(*rc4keyOut, 16, digest);

    HMAC_setup(ctx, secretKey, 128);
    HMAC_crunch(ctx, pubKeyOut, 128);
#if defined(USE_MBEDTLS) || defined(USE_POLARSSL) || defined(USE_GNUTLS)
    HMAC_finish(ctx, digest);
#else
    HMAC_finish(ctx, digest, digestLen);
#endif

    RTMP_Log(RTMP_LOGDEBUG, "RC4 In Key: ");
    RTMP_LogHex(RTMP_LOGDEBUG, digest, 16);

    RC4_setkey(*rc4keyIn, 16, digest);
}