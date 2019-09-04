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
struct nfsd4_sessionid {scalar_t__ reserved; scalar_t__ sequence; int /*<<< orphan*/  clientid; } ;
struct TYPE_2__ {scalar_t__ data; } ;
struct nfsd4_session {TYPE_1__ se_sessionid; struct nfs4_client* se_client; } ;
struct nfs4_client {int /*<<< orphan*/  cl_clientid; } ;

/* Variables and functions */
 int /*<<< orphan*/  current_sessionid ; 

__attribute__((used)) static void
gen_sessionid(struct nfsd4_session *ses)
{
	struct nfs4_client *clp = ses->se_client;
	struct nfsd4_sessionid *sid;

	sid = (struct nfsd4_sessionid *)ses->se_sessionid.data;
	sid->clientid = clp->cl_clientid;
	sid->sequence = current_sessionid++;
	sid->reserved = 0;
}