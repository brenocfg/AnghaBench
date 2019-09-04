#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int msr; TYPE_2__* ops; } ;
struct srcimp {int mapped; TYPE_4__ rsc; TYPE_5__* mgr; struct imapper* imappers; } ;
struct TYPE_16__ {TYPE_1__* ops; } ;
struct src {TYPE_7__ rsc; } ;
struct rsc {TYPE_3__* ops; } ;
struct imapper {int /*<<< orphan*/  addr; int /*<<< orphan*/  user; int /*<<< orphan*/  slot; } ;
struct TYPE_15__ {int /*<<< orphan*/  (* imap_add ) (TYPE_5__*,struct imapper*) ;} ;
struct TYPE_13__ {int /*<<< orphan*/  (* master ) (struct rsc*) ;int /*<<< orphan*/  (* next_conj ) (struct rsc*) ;int /*<<< orphan*/  (* output_slot ) (struct rsc*) ;} ;
struct TYPE_12__ {int /*<<< orphan*/  (* master ) (TYPE_4__*) ;int /*<<< orphan*/  (* next_conj ) (TYPE_4__*) ;int /*<<< orphan*/  (* index ) (TYPE_4__*) ;} ;
struct TYPE_11__ {int /*<<< orphan*/  (* index ) (TYPE_7__*) ;int /*<<< orphan*/  (* master ) (TYPE_7__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 
 int /*<<< orphan*/  stub10 (TYPE_4__*) ; 
 int /*<<< orphan*/  stub11 (struct rsc*) ; 
 int /*<<< orphan*/  stub2 (TYPE_7__*) ; 
 int /*<<< orphan*/  stub3 (struct rsc*) ; 
 int /*<<< orphan*/  stub4 (struct rsc*) ; 
 int /*<<< orphan*/  stub5 (TYPE_7__*) ; 
 int /*<<< orphan*/  stub6 (TYPE_4__*) ; 
 int /*<<< orphan*/  stub7 (TYPE_5__*,struct imapper*) ; 
 int /*<<< orphan*/  stub8 (TYPE_4__*) ; 
 int /*<<< orphan*/  stub9 (struct rsc*) ; 

__attribute__((used)) static int srcimp_map(struct srcimp *srcimp, struct src *src, struct rsc *input)
{
	struct imapper *entry;
	int i;

	srcimp->rsc.ops->master(&srcimp->rsc);
	src->rsc.ops->master(&src->rsc);
	input->ops->master(input);

	/* Program master and conjugate resources */
	for (i = 0; i < srcimp->rsc.msr; i++) {
		entry = &srcimp->imappers[i];
		entry->slot = input->ops->output_slot(input);
		entry->user = src->rsc.ops->index(&src->rsc);
		entry->addr = srcimp->rsc.ops->index(&srcimp->rsc);
		srcimp->mgr->imap_add(srcimp->mgr, entry);
		srcimp->mapped |= (0x1 << i);

		srcimp->rsc.ops->next_conj(&srcimp->rsc);
		input->ops->next_conj(input);
	}

	srcimp->rsc.ops->master(&srcimp->rsc);
	input->ops->master(input);

	return 0;
}