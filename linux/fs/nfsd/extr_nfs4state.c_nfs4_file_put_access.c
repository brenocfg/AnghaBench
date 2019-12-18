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
typedef  int u32 ;
struct nfs4_file {int dummy; } ;

/* Variables and functions */
 int NFS4_SHARE_ACCESS_BOTH ; 
 int NFS4_SHARE_ACCESS_READ ; 
 int NFS4_SHARE_ACCESS_WRITE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  O_WRONLY ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __nfs4_file_put_access (struct nfs4_file*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfs4_file_put_access(struct nfs4_file *fp, u32 access)
{
	WARN_ON_ONCE(access & ~NFS4_SHARE_ACCESS_BOTH);

	if (access & NFS4_SHARE_ACCESS_WRITE)
		__nfs4_file_put_access(fp, O_WRONLY);
	if (access & NFS4_SHARE_ACCESS_READ)
		__nfs4_file_put_access(fp, O_RDONLY);
}