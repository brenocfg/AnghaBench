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
typedef  TYPE_1__* pmbedtls_session ;
typedef  int /*<<< orphan*/  mbedtls_session ;
struct TYPE_3__ {int /*<<< orphan*/  pkey; int /*<<< orphan*/  clicert; int /*<<< orphan*/  cacert; } ;

/* Variables and functions */
 int /*<<< orphan*/  mbedtls_pk_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_x509_crt_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_zalloc (int) ; 

__attribute__((used)) static pmbedtls_session mbedtls_session_new(void)
{
	pmbedtls_session session = (pmbedtls_session)os_zalloc(sizeof(mbedtls_session));
	if (session){
		mbedtls_x509_crt_init(&session->cacert);
		mbedtls_x509_crt_init(&session->clicert);
		mbedtls_pk_init(&session->pkey);
//		mbedtls_entropy_init(&session->entropy);
	}
	return session;
}