#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * s; } ;
struct TYPE_4__ {TYPE_1__ message; } ;
typedef  TYPE_2__ MYSQLND_PACKET_STATS ;

/* Variables and functions */
 int /*<<< orphan*/  mnd_efree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
void php_mysqlnd_stats_free_mem(void * _packet)
{
	MYSQLND_PACKET_STATS *p= (MYSQLND_PACKET_STATS *) _packet;
	if (p->message.s) {
		mnd_efree(p->message.s);
		p->message.s = NULL;
	}
}