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
struct nf_log_buf {size_t count; scalar_t__* buf; } ;

/* Variables and functions */
 struct nf_log_buf emergency ; 
 struct nf_log_buf* emergency_ptr ; 
 int /*<<< orphan*/  kfree (struct nf_log_buf*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  printk (char*,scalar_t__*) ; 

void nf_log_buf_close(struct nf_log_buf *m)
{
	m->buf[m->count] = 0;
	printk("%s\n", m->buf);

	if (likely(m != &emergency))
		kfree(m);
	else {
		emergency_ptr = m;
		local_bh_enable();
	}
}