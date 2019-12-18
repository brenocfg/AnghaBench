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
struct TYPE_2__ {scalar_t__ new_auth_protocol_data_len; int /*<<< orphan*/ * new_auth_protocol_data; scalar_t__ new_auth_protocol_len; int /*<<< orphan*/ * new_auth_protocol; } ;
typedef  TYPE_1__ MYSQLND_PACKET_CHG_USER_RESPONSE ;

/* Variables and functions */
 int /*<<< orphan*/  mnd_efree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
php_mysqlnd_chg_user_free_mem(void * _packet)
{
	MYSQLND_PACKET_CHG_USER_RESPONSE * p = (MYSQLND_PACKET_CHG_USER_RESPONSE *) _packet;

	if (p->new_auth_protocol) {
		mnd_efree(p->new_auth_protocol);
		p->new_auth_protocol = NULL;
	}
	p->new_auth_protocol_len = 0;

	if (p->new_auth_protocol_data) {
		mnd_efree(p->new_auth_protocol_data);
		p->new_auth_protocol_data = NULL;
	}
	p->new_auth_protocol_data_len = 0;
}