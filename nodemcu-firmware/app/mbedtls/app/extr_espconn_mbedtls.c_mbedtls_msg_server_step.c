#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* pmbedtls_msg ;
typedef  int /*<<< orphan*/  mbedtls_msg ;
struct TYPE_8__ {int /*<<< orphan*/ * out_buf; } ;
struct TYPE_7__ {int /*<<< orphan*/  entropy; int /*<<< orphan*/  ctr_drbg; int /*<<< orphan*/  conf; TYPE_3__ ssl; int /*<<< orphan*/  fd; scalar_t__ psession; scalar_t__ quiet; } ;

/* Variables and functions */
 int /*<<< orphan*/  MBEDTLS_SSL_OUTBUFFER_LEN ; 
 int /*<<< orphan*/  lwIP_ASSERT (TYPE_1__*) ; 
 int /*<<< orphan*/  mbedtls_ctr_drbg_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_ctr_drbg_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_entropy_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_entropy_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_net_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_session_free (scalar_t__*) ; 
 scalar_t__ mbedtls_session_new () ; 
 int /*<<< orphan*/  mbedtls_ssl_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_ssl_config_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_ssl_free (TYPE_3__*) ; 
 int /*<<< orphan*/  mbedtls_ssl_init (TYPE_3__*) ; 
 int /*<<< orphan*/  mbedtls_zeroize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_bzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mbedtls_msg_server_step(pmbedtls_msg msg)
{
	lwIP_ASSERT(msg);

	/*to prevent memory leaks, ensure that each allocated is deleted at every handshake*/
	if (msg->psession){
		mbedtls_session_free(&msg->psession);
	}
#if defined(ESP8266_PLATFORM)
    if (msg->quiet && msg->ssl.out_buf)
    {
        mbedtls_zeroize(msg->ssl.out_buf, MBEDTLS_SSL_OUTBUFFER_LEN);
        os_free(msg->ssl.out_buf);
        msg->ssl.out_buf = NULL;
    }
#endif
	mbedtls_entropy_free(&msg->entropy);
	mbedtls_ssl_free(&msg->ssl);
	mbedtls_ssl_config_free(&msg->conf);
	mbedtls_ctr_drbg_free(&msg->ctr_drbg);

	/*New connection ensure that each initial for next handshake */
	os_bzero(msg, sizeof(mbedtls_msg));
	msg->psession = mbedtls_session_new();
	if (msg->psession){
		mbedtls_net_init(&msg->fd);
		mbedtls_ssl_init(&msg->ssl);
		mbedtls_ssl_config_init(&msg->conf);
		mbedtls_ctr_drbg_init(&msg->ctr_drbg);
		mbedtls_entropy_init(&msg->entropy);
	}
}