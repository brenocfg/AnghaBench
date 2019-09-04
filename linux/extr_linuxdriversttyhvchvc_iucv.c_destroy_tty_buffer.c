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
struct iucv_tty_buffer {int /*<<< orphan*/  mbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  hvc_iucv_mempool ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (struct iucv_tty_buffer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void destroy_tty_buffer(struct iucv_tty_buffer *bufp)
{
	kfree(bufp->mbuf);
	mempool_free(bufp, hvc_iucv_mempool);
}