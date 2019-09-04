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
struct rchan_buf {int bytes_consumed; TYPE_1__* chan; int /*<<< orphan*/  cpu; } ;
struct TYPE_2__ {int subbuf_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  relay_subbufs_consumed (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void relay_consume_bytes(struct rchan_buf *rbuf, int bytes_consumed)
{
	rbuf->bytes_consumed += bytes_consumed;

	if (rbuf->bytes_consumed >= rbuf->chan->subbuf_size) {
		relay_subbufs_consumed(rbuf->chan, rbuf->cpu, 1);
		rbuf->bytes_consumed %= rbuf->chan->subbuf_size;
	}
}