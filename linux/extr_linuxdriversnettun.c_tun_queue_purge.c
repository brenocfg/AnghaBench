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
struct TYPE_2__ {int /*<<< orphan*/  sk_error_queue; int /*<<< orphan*/  sk_write_queue; } ;
struct tun_file {TYPE_1__ sk; int /*<<< orphan*/  tx_ring; } ;

/* Variables and functions */
 void* ptr_ring_consume (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tun_ptr_free (void*) ; 

__attribute__((used)) static void tun_queue_purge(struct tun_file *tfile)
{
	void *ptr;

	while ((ptr = ptr_ring_consume(&tfile->tx_ring)) != NULL)
		tun_ptr_free(ptr);

	skb_queue_purge(&tfile->sk.sk_write_queue);
	skb_queue_purge(&tfile->sk.sk_error_queue);
}