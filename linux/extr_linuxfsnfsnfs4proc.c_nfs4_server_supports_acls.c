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
struct nfs_server {int caps; } ;

/* Variables and functions */
 int NFS_CAP_ACLS ; 

__attribute__((used)) static inline int nfs4_server_supports_acls(struct nfs_server *server)
{
	return server->caps & NFS_CAP_ACLS;
}