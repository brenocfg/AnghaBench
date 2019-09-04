#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long u32 ;
struct qdio_q {int /*<<< orphan*/  mask; TYPE_1__* irq_ptr; int /*<<< orphan*/  nr; } ;
struct TYPE_2__ {unsigned long sch_token; int /*<<< orphan*/  schid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_DEV_EVENT (int /*<<< orphan*/ ,TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBF_ERROR (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DBF_INFO ; 
 int EIO ; 
 unsigned int QDIO_SIGA_QEBSM_FLAG ; 
 unsigned int QDIO_SIGA_READ ; 
 int /*<<< orphan*/  SCH_NO (struct qdio_q*) ; 
 int do_siga_input (unsigned long,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ is_qebsm (struct qdio_q*) ; 
 int /*<<< orphan*/  qperf_inc (struct qdio_q*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siga_read ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int qdio_siga_input(struct qdio_q *q)
{
	unsigned long schid = *((u32 *) &q->irq_ptr->schid);
	unsigned int fc = QDIO_SIGA_READ;
	int cc;

	DBF_DEV_EVENT(DBF_INFO, q->irq_ptr, "siga-r:%1d", q->nr);
	qperf_inc(q, siga_read);

	if (is_qebsm(q)) {
		schid = q->irq_ptr->sch_token;
		fc |= QDIO_SIGA_QEBSM_FLAG;
	}

	cc = do_siga_input(schid, q->mask, fc);
	if (unlikely(cc))
		DBF_ERROR("%4x SIGA-R:%2d", SCH_NO(q), cc);
	return (cc) ? -EIO : 0;
}