#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_5__ {int /*<<< orphan*/  icv_truncbits; } ;
struct TYPE_6__ {TYPE_2__ auth; } ;
struct TYPE_4__ {int /*<<< orphan*/  sadb_alg_id; } ;
struct xfrm_algo_desc {TYPE_3__ uinfo; int /*<<< orphan*/  name; TYPE_1__ desc; } ;
struct xfrm_algo_auth {int alg_key_len; int /*<<< orphan*/  alg_key; int /*<<< orphan*/  alg_trunc_len; int /*<<< orphan*/  alg_name; } ;
struct xfrm_algo {int alg_key_len; int /*<<< orphan*/  alg_key; int /*<<< orphan*/  alg_name; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct xfrm_algo_auth* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct xfrm_algo* nla_data (struct nlattr*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct xfrm_algo_desc* xfrm_aalg_get_byname (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int attach_auth(struct xfrm_algo_auth **algpp, u8 *props,
		       struct nlattr *rta)
{
	struct xfrm_algo *ualg;
	struct xfrm_algo_auth *p;
	struct xfrm_algo_desc *algo;

	if (!rta)
		return 0;

	ualg = nla_data(rta);

	algo = xfrm_aalg_get_byname(ualg->alg_name, 1);
	if (!algo)
		return -ENOSYS;
	*props = algo->desc.sadb_alg_id;

	p = kmalloc(sizeof(*p) + (ualg->alg_key_len + 7) / 8, GFP_KERNEL);
	if (!p)
		return -ENOMEM;

	strcpy(p->alg_name, algo->name);
	p->alg_key_len = ualg->alg_key_len;
	p->alg_trunc_len = algo->uinfo.auth.icv_truncbits;
	memcpy(p->alg_key, ualg->alg_key, (ualg->alg_key_len + 7) / 8);

	*algpp = p;
	return 0;
}