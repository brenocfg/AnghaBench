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
struct bfa_uf_mod_s {void* cbarg; int /*<<< orphan*/  ufrecv; } ;
struct bfa_s {int dummy; } ;
typedef  int /*<<< orphan*/  bfa_cb_uf_recv_t ;

/* Variables and functions */
 struct bfa_uf_mod_s* BFA_UF_MOD (struct bfa_s*) ; 

void
bfa_uf_recv_register(struct bfa_s *bfa, bfa_cb_uf_recv_t ufrecv, void *cbarg)
{
	struct bfa_uf_mod_s *ufm = BFA_UF_MOD(bfa);

	ufm->ufrecv = ufrecv;
	ufm->cbarg = cbarg;
}