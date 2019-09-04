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
typedef  int /*<<< orphan*/  u_long ;
struct TYPE_4__ {scalar_t__ baddr; struct TYPE_4__* next; scalar_t__ vaddr; } ;
typedef  TYPE_1__ m_vtob_s ;
struct TYPE_5__ {TYPE_1__** vtob; } ;
typedef  TYPE_2__ m_pool_s ;
typedef  int /*<<< orphan*/  m_bush_t ;
typedef  scalar_t__ m_addr_t ;

/* Variables and functions */
 scalar_t__ MEMO_CLUSTER_MASK ; 
 int VTOB_HASH_CODE (void*) ; 
 TYPE_2__* ___get_dma_pool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ncr53c8xx_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static m_addr_t __vtobus(m_bush_t bush, void *m)
{
	u_long flags;
	m_pool_s *mp;
	int hc = VTOB_HASH_CODE(m);
	m_vtob_s *vp = NULL;
	m_addr_t a = ((m_addr_t) m) & ~MEMO_CLUSTER_MASK;

	spin_lock_irqsave(&ncr53c8xx_lock, flags);
	mp = ___get_dma_pool(bush);
	if (mp) {
		vp = mp->vtob[hc];
		while (vp && (m_addr_t) vp->vaddr != a)
			vp = vp->next;
	}
	spin_unlock_irqrestore(&ncr53c8xx_lock, flags);
	return vp ? vp->baddr + (((m_addr_t) m) - a) : 0;
}