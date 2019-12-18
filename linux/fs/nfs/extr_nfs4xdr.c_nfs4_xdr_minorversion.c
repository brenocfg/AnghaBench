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
typedef  int /*<<< orphan*/  u32 ;
struct nfs4_session {TYPE_4__* clp; } ;
struct nfs4_sequence_args {TYPE_2__* sa_slot; } ;
struct TYPE_8__ {TYPE_3__* cl_mvops; } ;
struct TYPE_7__ {int /*<<< orphan*/  minor_version; } ;
struct TYPE_6__ {TYPE_1__* table; } ;
struct TYPE_5__ {struct nfs4_session* session; } ;

/* Variables and functions */

__attribute__((used)) static u32 nfs4_xdr_minorversion(const struct nfs4_sequence_args *args)
{
#if defined(CONFIG_NFS_V4_1)
	struct nfs4_session *session = args->sa_slot->table->session;
	if (session)
		return session->clp->cl_mvops->minor_version;
#endif /* CONFIG_NFS_V4_1 */
	return 0;
}