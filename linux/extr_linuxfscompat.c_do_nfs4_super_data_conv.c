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
struct nfs4_mount_data {int /*<<< orphan*/  version; int /*<<< orphan*/  flags; int /*<<< orphan*/  rsize; int /*<<< orphan*/  wsize; int /*<<< orphan*/  timeo; int /*<<< orphan*/  retrans; int /*<<< orphan*/  acregmin; int /*<<< orphan*/  acregmax; int /*<<< orphan*/  acdirmin; int /*<<< orphan*/  acdirmax; int /*<<< orphan*/  client_addr; int /*<<< orphan*/  mnt_path; int /*<<< orphan*/  hostname; int /*<<< orphan*/  host_addrlen; void* host_addr; int /*<<< orphan*/  proto; int /*<<< orphan*/  auth_flavourlen; void* auth_flavours; } ;
struct compat_nfs4_mount_data_v1 {int /*<<< orphan*/  version; int /*<<< orphan*/  flags; int /*<<< orphan*/  rsize; int /*<<< orphan*/  wsize; int /*<<< orphan*/  timeo; int /*<<< orphan*/  retrans; int /*<<< orphan*/  acregmin; int /*<<< orphan*/  acregmax; int /*<<< orphan*/  acdirmin; int /*<<< orphan*/  acdirmax; int /*<<< orphan*/  client_addr; int /*<<< orphan*/  mnt_path; int /*<<< orphan*/  hostname; int /*<<< orphan*/  host_addrlen; int /*<<< orphan*/  host_addr; int /*<<< orphan*/  proto; int /*<<< orphan*/  auth_flavourlen; int /*<<< orphan*/  auth_flavours; } ;
typedef  int compat_uint_t ;

/* Variables and functions */
 int /*<<< orphan*/  compat_nfs_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* compat_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_nfs4_super_data_conv(void *raw_data)
{
	int version = *(compat_uint_t *) raw_data;

	if (version == 1) {
		struct compat_nfs4_mount_data_v1 *raw = raw_data;
		struct nfs4_mount_data *real = raw_data;

		/* copy the fields backwards */
		real->auth_flavours = compat_ptr(raw->auth_flavours);
		real->auth_flavourlen = raw->auth_flavourlen;
		real->proto = raw->proto;
		real->host_addr = compat_ptr(raw->host_addr);
		real->host_addrlen = raw->host_addrlen;
		compat_nfs_string(&real->hostname, &raw->hostname);
		compat_nfs_string(&real->mnt_path, &raw->mnt_path);
		compat_nfs_string(&real->client_addr, &raw->client_addr);
		real->acdirmax = raw->acdirmax;
		real->acdirmin = raw->acdirmin;
		real->acregmax = raw->acregmax;
		real->acregmin = raw->acregmin;
		real->retrans = raw->retrans;
		real->timeo = raw->timeo;
		real->wsize = raw->wsize;
		real->rsize = raw->rsize;
		real->flags = raw->flags;
		real->version = raw->version;
	}

	return 0;
}