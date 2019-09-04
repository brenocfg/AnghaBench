#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* m_pool_p ;
struct TYPE_7__ {TYPE_1__* next; } ;
struct TYPE_6__ {struct TYPE_6__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  __sym_mfree (TYPE_2__*,TYPE_1__*,int,char*) ; 
 TYPE_2__ mp0 ; 

__attribute__((used)) static void ___del_dma_pool(m_pool_p p)
{
	m_pool_p *pp = &mp0.next;

	while (*pp && *pp != p)
		pp = &(*pp)->next;
	if (*pp) {
		*pp = (*pp)->next;
		__sym_mfree(&mp0, p, sizeof(*p), "MPOOL");
	}
}