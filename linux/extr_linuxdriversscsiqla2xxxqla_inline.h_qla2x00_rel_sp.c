#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_5__* vha; } ;
typedef  TYPE_2__ srb_t ;
struct TYPE_8__ {TYPE_1__* hw; } ;
struct TYPE_6__ {int /*<<< orphan*/  srb_mempool; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLA_VHA_MARK_NOT_BUSY (TYPE_5__*) ; 
 int /*<<< orphan*/  mempool_free (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
qla2x00_rel_sp(srb_t *sp)
{
	QLA_VHA_MARK_NOT_BUSY(sp->vha);
	mempool_free(sp, sp->vha->hw->srb_mempool);
}