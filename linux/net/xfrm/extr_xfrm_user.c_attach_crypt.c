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
struct TYPE_5__ {int /*<<< orphan*/  ealgo; } ;
struct xfrm_state {int /*<<< orphan*/  geniv; struct xfrm_algo* ealg; TYPE_1__ props; } ;
struct TYPE_7__ {int /*<<< orphan*/  geniv; } ;
struct TYPE_8__ {TYPE_3__ encr; } ;
struct TYPE_6__ {int /*<<< orphan*/  sadb_alg_id; } ;
struct xfrm_algo_desc {TYPE_4__ uinfo; int /*<<< orphan*/  name; TYPE_2__ desc; } ;
struct xfrm_algo {int /*<<< orphan*/  alg_name; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct xfrm_algo* kmemdup (struct xfrm_algo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct xfrm_algo* nla_data (struct nlattr*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_alg_len (struct xfrm_algo*) ; 
 struct xfrm_algo_desc* xfrm_ealg_get_byname (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int attach_crypt(struct xfrm_state *x, struct nlattr *rta)
{
	struct xfrm_algo *p, *ualg;
	struct xfrm_algo_desc *algo;

	if (!rta)
		return 0;

	ualg = nla_data(rta);

	algo = xfrm_ealg_get_byname(ualg->alg_name, 1);
	if (!algo)
		return -ENOSYS;
	x->props.ealgo = algo->desc.sadb_alg_id;

	p = kmemdup(ualg, xfrm_alg_len(ualg), GFP_KERNEL);
	if (!p)
		return -ENOMEM;

	strcpy(p->alg_name, algo->name);
	x->ealg = p;
	x->geniv = algo->uinfo.encr.geniv;
	return 0;
}