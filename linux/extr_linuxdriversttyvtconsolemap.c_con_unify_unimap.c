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
typedef  int /*<<< orphan*/  u16 ;
struct vc_data {struct uni_pagedir** vc_uni_pagedir_loc; } ;
struct uni_pagedir {scalar_t__ sum; int /*<<< orphan*/  refcount; int /*<<< orphan*/ *** uni_pgdir; } ;
struct TYPE_4__ {TYPE_1__* d; } ;
struct TYPE_3__ {struct uni_pagedir** vc_uni_pagedir_loc; } ;

/* Variables and functions */
 int MAX_NR_CONSOLES ; 
 int /*<<< orphan*/  con_release_unimap (struct uni_pagedir*) ; 
 int /*<<< orphan*/  kfree (struct uni_pagedir*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_2__* vc_cons ; 
 int /*<<< orphan*/  vc_cons_allocated (int) ; 

__attribute__((used)) static int con_unify_unimap(struct vc_data *conp, struct uni_pagedir *p)
{
	int i, j, k;
	struct uni_pagedir *q;
	
	for (i = 0; i < MAX_NR_CONSOLES; i++) {
		if (!vc_cons_allocated(i))
			continue;
		q = *vc_cons[i].d->vc_uni_pagedir_loc;
		if (!q || q == p || q->sum != p->sum)
			continue;
		for (j = 0; j < 32; j++) {
			u16 **p1, **q1;
			p1 = p->uni_pgdir[j]; q1 = q->uni_pgdir[j];
			if (!p1 && !q1)
				continue;
			if (!p1 || !q1)
				break;
			for (k = 0; k < 32; k++) {
				if (!p1[k] && !q1[k])
					continue;
				if (!p1[k] || !q1[k])
					break;
				if (memcmp(p1[k], q1[k], 64*sizeof(u16)))
					break;
			}
			if (k < 32)
				break;
		}
		if (j == 32) {
			q->refcount++;
			*conp->vc_uni_pagedir_loc = q;
			con_release_unimap(p);
			kfree(p);
			return 1;
		}
	}
	return 0;
}