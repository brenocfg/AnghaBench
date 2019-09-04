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
struct nf_log_buf {scalar_t__ count; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  emergency_ptr ; 
 struct nf_log_buf* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 scalar_t__ unlikely (int) ; 
 struct nf_log_buf* xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

struct nf_log_buf *nf_log_buf_open(void)
{
	struct nf_log_buf *m = kmalloc(sizeof(*m), GFP_ATOMIC);

	if (unlikely(!m)) {
		local_bh_disable();
		do {
			m = xchg(&emergency_ptr, NULL);
		} while (!m);
	}
	m->count = 0;
	return m;
}