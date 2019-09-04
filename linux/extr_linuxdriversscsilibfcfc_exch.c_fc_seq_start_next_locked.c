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
struct fc_seq {int /*<<< orphan*/  id; } ;
struct fc_exch {int /*<<< orphan*/  f_ctl; int /*<<< orphan*/  seq_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_EXCH_DBG (struct fc_exch*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fc_seq* fc_seq_alloc (struct fc_exch*,int /*<<< orphan*/ ) ; 
 struct fc_exch* fc_seq_exch (struct fc_seq*) ; 

__attribute__((used)) static struct fc_seq *fc_seq_start_next_locked(struct fc_seq *sp)
{
	struct fc_exch *ep = fc_seq_exch(sp);

	sp = fc_seq_alloc(ep, ep->seq_id++);
	FC_EXCH_DBG(ep, "f_ctl %6x seq %2x\n",
		    ep->f_ctl, sp->id);
	return sp;
}