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
struct TYPE_2__ {int /*<<< orphan*/  callback; } ;
struct nfsd4_conn {TYPE_1__ cn_xpt_user; int /*<<< orphan*/  cn_xprt; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfsd4_conn_lost ; 
 int register_xpt_user (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int nfsd4_register_conn(struct nfsd4_conn *conn)
{
	conn->cn_xpt_user.callback = nfsd4_conn_lost;
	return register_xpt_user(conn->cn_xprt, &conn->cn_xpt_user);
}