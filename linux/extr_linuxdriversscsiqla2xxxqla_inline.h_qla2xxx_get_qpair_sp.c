#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct qla_qpair {int /*<<< orphan*/  vha; int /*<<< orphan*/  srb_mempool; } ;
struct TYPE_5__ {int iocbs; int /*<<< orphan*/  elem; int /*<<< orphan*/  vha; int /*<<< orphan*/ * fcport; } ;
typedef  TYPE_1__ srb_t ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  fc_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  QLA_QPAIR_MARK_BUSY (struct qla_qpair*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QLA_QPAIR_MARK_NOT_BUSY (struct qla_qpair*) ; 
 TYPE_1__* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline srb_t *
qla2xxx_get_qpair_sp(struct qla_qpair *qpair, fc_port_t *fcport, gfp_t flag)
{
	srb_t *sp = NULL;
	uint8_t bail;

	QLA_QPAIR_MARK_BUSY(qpair, bail);
	if (unlikely(bail))
		return NULL;

	sp = mempool_alloc(qpair->srb_mempool, flag);
	if (!sp)
		goto done;

	memset(sp, 0, sizeof(*sp));
	sp->fcport = fcport;
	sp->iocbs = 1;
	sp->vha = qpair->vha;
	INIT_LIST_HEAD(&sp->elem);

done:
	if (!sp)
		QLA_QPAIR_MARK_NOT_BUSY(qpair);
	return sp;
}