#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * dir_attr; int /*<<< orphan*/ * fattr; int /*<<< orphan*/ * fh; } ;
struct TYPE_3__ {TYPE_2__* rpc_resp; int /*<<< orphan*/ * rpc_argp; } ;
struct nfs3_createdata {TYPE_2__ res; int /*<<< orphan*/  dir_attr; int /*<<< orphan*/  fattr; int /*<<< orphan*/  fh; TYPE_1__ msg; int /*<<< orphan*/  arg; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nfs3_createdata* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_fattr_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct nfs3_createdata *nfs3_alloc_createdata(void)
{
	struct nfs3_createdata *data;

	data = kzalloc(sizeof(*data), GFP_KERNEL);
	if (data != NULL) {
		data->msg.rpc_argp = &data->arg;
		data->msg.rpc_resp = &data->res;
		data->res.fh = &data->fh;
		data->res.fattr = &data->fattr;
		data->res.dir_attr = &data->dir_attr;
		nfs_fattr_init(data->res.fattr);
		nfs_fattr_init(data->res.dir_attr);
	}
	return data;
}