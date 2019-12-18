#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* pmbedtls_msg ;
typedef  int /*<<< orphan*/  mbedtls_msg ;
struct TYPE_5__ {int /*<<< orphan*/  conf; int /*<<< orphan*/  entropy; int /*<<< orphan*/  ctr_drbg; int /*<<< orphan*/  ssl; int /*<<< orphan*/  fd; int /*<<< orphan*/  listen_fd; scalar_t__ psession; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_MAX_FRAGMENT_LENGTH_CODE ; 
 int /*<<< orphan*/  mbedtls_ctr_drbg_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_entropy_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_net_init (int /*<<< orphan*/ *) ; 
 scalar_t__ mbedtls_session_new () ; 
 int /*<<< orphan*/  mbedtls_ssl_conf_max_frag_len (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_ssl_config_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_ssl_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_bzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  os_free (TYPE_1__*) ; 
 int /*<<< orphan*/  os_zalloc (int) ; 

__attribute__((used)) static pmbedtls_msg mbedtls_msg_new(void)
{
	pmbedtls_msg msg = (pmbedtls_msg)os_zalloc( sizeof(mbedtls_msg));
	if (msg) {
		os_bzero(msg, sizeof(mbedtls_msg));
		msg->psession = mbedtls_session_new();
		if (msg->psession){
			mbedtls_net_init(&msg->listen_fd);
			mbedtls_net_init(&msg->fd);
			mbedtls_ssl_init(&msg->ssl);
			mbedtls_ssl_config_init(&msg->conf);
			mbedtls_ctr_drbg_init(&msg->ctr_drbg);
			mbedtls_entropy_init(&msg->entropy);
#if defined(MBEDTLS_SSL_MAX_FRAGMENT_LENGTH) && defined(SSL_MAX_FRAGMENT_LENGTH_CODE)
			mbedtls_ssl_conf_max_frag_len(&msg->conf, SSL_MAX_FRAGMENT_LENGTH_CODE);
#endif
		} else{
			os_free(msg);
			msg = NULL;
		}
	}
	return msg;
}