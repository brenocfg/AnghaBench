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
typedef  int u16 ;
struct list_head {int dummy; } ;
struct bfa_uf_mod_s {int num_ufs; int /*<<< orphan*/  uf_unused_q; int /*<<< orphan*/  uf_free_q; } ;
struct bfa_s {int dummy; } ;

/* Variables and functions */
 struct bfa_uf_mod_s* BFA_UF_MOD (struct bfa_s*) ; 
 int /*<<< orphan*/  bfa_q_deq_tail (int /*<<< orphan*/ *,struct list_head**) ; 
 int /*<<< orphan*/  list_add_tail (struct list_head*,int /*<<< orphan*/ *) ; 

void
bfa_uf_res_recfg(struct bfa_s *bfa, u16 num_uf_fw)
{
	struct bfa_uf_mod_s	*mod = BFA_UF_MOD(bfa);
	struct list_head	*qe;
	int	i;

	for (i = 0; i < (mod->num_ufs - num_uf_fw); i++) {
		bfa_q_deq_tail(&mod->uf_free_q, &qe);
		list_add_tail(qe, &mod->uf_unused_q);
	}
}