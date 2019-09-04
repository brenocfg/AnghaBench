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
typedef  int /*<<< orphan*/  u32 ;
struct nfs4_sequence_args {int dummy; } ;

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