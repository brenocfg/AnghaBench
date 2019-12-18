#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xdr_stream {int dummy; } ;
struct nfs_entry {TYPE_1__* fattr; } ;
struct TYPE_5__ {int (* decode ) (struct xdr_stream*,struct nfs_entry*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  gencount; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  plus; } ;
typedef  TYPE_2__ nfs_readdir_descriptor_t ;
struct TYPE_4__ {int /*<<< orphan*/  gencount; int /*<<< orphan*/  time_start; } ;

/* Variables and functions */
 int stub1 (struct xdr_stream*,struct nfs_entry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xdr_decode(nfs_readdir_descriptor_t *desc,
		      struct nfs_entry *entry, struct xdr_stream *xdr)
{
	int error;

	error = desc->decode(xdr, entry, desc->plus);
	if (error)
		return error;
	entry->fattr->time_start = desc->timestamp;
	entry->fattr->gencount = desc->gencount;
	return 0;
}