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
struct nfsd4_session {int /*<<< orphan*/  se_conns; } ;
struct nfsd4_conn {int /*<<< orphan*/  cn_persession; struct nfsd4_session* cn_session; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __nfsd4_hash_conn(struct nfsd4_conn *conn, struct nfsd4_session *ses)
{
	conn->cn_session = ses;
	list_add(&conn->cn_persession, &ses->se_conns);
}