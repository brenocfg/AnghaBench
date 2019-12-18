#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct l2cap_conn {TYPE_3__* hcon; } ;
struct device {int dummy; } ;
struct bnep_session {TYPE_2__* sock; } ;
struct TYPE_8__ {TYPE_1__* chan; } ;
struct TYPE_7__ {struct device dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  sk; } ;
struct TYPE_5__ {struct l2cap_conn* conn; } ;

/* Variables and functions */
 TYPE_4__* l2cap_pi (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct device *bnep_get_device(struct bnep_session *session)
{
	struct l2cap_conn *conn = l2cap_pi(session->sock->sk)->chan->conn;

	if (!conn || !conn->hcon)
		return NULL;

	return &conn->hcon->dev;
}