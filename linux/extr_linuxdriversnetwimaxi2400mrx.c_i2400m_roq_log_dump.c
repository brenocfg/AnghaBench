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
struct i2400m_roq_log_entry {int dummy; } ;
struct i2400m_roq {TYPE_1__* log; } ;
struct i2400m {int dummy; } ;
struct TYPE_2__ {unsigned int out; unsigned int in; struct i2400m_roq_log_entry* entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int I2400M_ROQ_LOG_LENGTH ; 
 int __i2400m_roq_index (struct i2400m*,struct i2400m_roq*) ; 
 int /*<<< orphan*/  i2400m_roq_log_entry_print (struct i2400m*,int,unsigned int,struct i2400m_roq_log_entry*) ; 
 int /*<<< orphan*/  memset (struct i2400m_roq_log_entry*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static
void i2400m_roq_log_dump(struct i2400m *i2400m, struct i2400m_roq *roq)
{
	unsigned cnt, cnt_idx;
	struct i2400m_roq_log_entry *e;
	int index = __i2400m_roq_index(i2400m, roq);

	BUG_ON(roq->log->out > roq->log->in);
	for (cnt = roq->log->out; cnt < roq->log->in; cnt++) {
		cnt_idx = cnt % I2400M_ROQ_LOG_LENGTH;
		e = &roq->log->entry[cnt_idx];
		i2400m_roq_log_entry_print(i2400m, index, cnt_idx, e);
		memset(e, 0, sizeof(*e));
	}
	roq->log->in = roq->log->out = 0;
}