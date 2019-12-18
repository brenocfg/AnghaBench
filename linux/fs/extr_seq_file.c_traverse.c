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
struct seq_file {scalar_t__ count; scalar_t__ from; int size; void* buf; TYPE_1__* op; int /*<<< orphan*/  index; scalar_t__ version; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {int (* show ) (struct seq_file*,void*) ;int /*<<< orphan*/  (* stop ) (struct seq_file*,void*) ;void* (* next ) (struct seq_file*,void*,int /*<<< orphan*/ *) ;void* (* start ) (struct seq_file*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PAGE_SIZE ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  kvfree (void*) ; 
 void* seq_buf_alloc (int) ; 
 scalar_t__ seq_has_overflowed (struct seq_file*) ; 
 void* stub1 (struct seq_file*,int /*<<< orphan*/ *) ; 
 int stub2 (struct seq_file*,void*) ; 
 void* stub3 (struct seq_file*,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (struct seq_file*,void*) ; 
 int /*<<< orphan*/  stub5 (struct seq_file*,void*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int traverse(struct seq_file *m, loff_t offset)
{
	loff_t pos = 0;
	int error = 0;
	void *p;

	m->version = 0;
	m->index = 0;
	m->count = m->from = 0;
	if (!offset)
		return 0;

	if (!m->buf) {
		m->buf = seq_buf_alloc(m->size = PAGE_SIZE);
		if (!m->buf)
			return -ENOMEM;
	}
	p = m->op->start(m, &m->index);
	while (p) {
		error = PTR_ERR(p);
		if (IS_ERR(p))
			break;
		error = m->op->show(m, p);
		if (error < 0)
			break;
		if (unlikely(error)) {
			error = 0;
			m->count = 0;
		}
		if (seq_has_overflowed(m))
			goto Eoverflow;
		p = m->op->next(m, p, &m->index);
		if (pos + m->count > offset) {
			m->from = offset - pos;
			m->count -= m->from;
			break;
		}
		pos += m->count;
		m->count = 0;
		if (pos == offset)
			break;
	}
	m->op->stop(m, p);
	return error;

Eoverflow:
	m->op->stop(m, p);
	kvfree(m->buf);
	m->count = 0;
	m->buf = seq_buf_alloc(m->size <<= 1);
	return !m->buf ? -ENOMEM : -EAGAIN;
}