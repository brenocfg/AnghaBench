#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  cl_id; int /*<<< orphan*/  cl_boot; } ;
struct nfsd4_sessionid {TYPE_2__ clientid; } ;
struct TYPE_5__ {scalar_t__ data; } ;
struct nfsd4_session {TYPE_1__ se_sessionid; } ;
struct TYPE_7__ {int /*<<< orphan*/  cl_id; int /*<<< orphan*/  cl_boot; } ;
typedef  TYPE_3__ clientid_t ;

/* Variables and functions */

__attribute__((used)) static void
copy_clientid(clientid_t *clid, struct nfsd4_session *session)
{
	struct nfsd4_sessionid *sid =
			(struct nfsd4_sessionid *)session->se_sessionid.data;

	clid->cl_boot = sid->clientid.cl_boot;
	clid->cl_id = sid->clientid.cl_id;
}