#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* pmbedtls_espconn ;
typedef  int /*<<< orphan*/  mbedtls_espconn ;
typedef  int /*<<< orphan*/  esp_tcp ;
struct TYPE_5__ {int /*<<< orphan*/ * tcp; } ;
struct TYPE_6__ {TYPE_1__ proto; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (TYPE_2__*) ; 
 scalar_t__ os_zalloc (int) ; 

__attribute__((used)) static pmbedtls_espconn mbedtls_espconn_new(void)
{
	pmbedtls_espconn mbedtls_conn = NULL;
	mbedtls_conn = (pmbedtls_espconn)os_zalloc(sizeof(mbedtls_espconn));
	if (mbedtls_conn){
		mbedtls_conn->proto.tcp = (esp_tcp *)os_zalloc(sizeof(esp_tcp));
		if (mbedtls_conn->proto.tcp == NULL){
			os_free(mbedtls_conn);
			mbedtls_conn = NULL;
		}
	}

	return mbedtls_conn;
}