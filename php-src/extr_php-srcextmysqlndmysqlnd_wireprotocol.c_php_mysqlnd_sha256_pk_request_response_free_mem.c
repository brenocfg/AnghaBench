#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ public_key_len; int /*<<< orphan*/ * public_key; } ;
typedef  TYPE_1__ MYSQLND_PACKET_SHA256_PK_REQUEST_RESPONSE ;

/* Variables and functions */
 int /*<<< orphan*/  mnd_efree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
php_mysqlnd_sha256_pk_request_response_free_mem(void * _packet)
{
	MYSQLND_PACKET_SHA256_PK_REQUEST_RESPONSE * p = (MYSQLND_PACKET_SHA256_PK_REQUEST_RESPONSE *) _packet;
	if (p->public_key) {
		mnd_efree(p->public_key);
		p->public_key = NULL;
	}
	p->public_key_len = 0;
}