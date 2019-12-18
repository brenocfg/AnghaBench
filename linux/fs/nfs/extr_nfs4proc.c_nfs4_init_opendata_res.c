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
struct TYPE_8__ {int /*<<< orphan*/  access; int /*<<< orphan*/  server; int /*<<< orphan*/  seqid; } ;
struct TYPE_7__ {int /*<<< orphan*/  access_request; int /*<<< orphan*/  server; int /*<<< orphan*/  seqid; int /*<<< orphan*/  f_label; int /*<<< orphan*/ * f_attr; } ;
struct TYPE_6__ {int /*<<< orphan*/  seqid; } ;
struct TYPE_5__ {int /*<<< orphan*/  seqid; } ;
struct nfs4_opendata {int /*<<< orphan*/  group_name; int /*<<< orphan*/  owner_name; int /*<<< orphan*/  f_attr; TYPE_4__ o_arg; TYPE_3__ o_res; TYPE_2__ c_arg; TYPE_1__ c_res; int /*<<< orphan*/  f_label; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfs_fattr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_fattr_init_names (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs4_init_opendata_res(struct nfs4_opendata *p)
{
	p->o_res.f_attr = &p->f_attr;
	p->o_res.f_label = p->f_label;
	p->o_res.seqid = p->o_arg.seqid;
	p->c_res.seqid = p->c_arg.seqid;
	p->o_res.server = p->o_arg.server;
	p->o_res.access_request = p->o_arg.access;
	nfs_fattr_init(&p->f_attr);
	nfs_fattr_init_names(&p->f_attr, &p->owner_name, &p->group_name);
}