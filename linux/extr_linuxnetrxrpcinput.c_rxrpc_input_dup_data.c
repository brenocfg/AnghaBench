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
typedef  scalar_t__ u8 ;
struct rxrpc_call {int /*<<< orphan*/  nr_jumbo_bad; } ;
typedef  int /*<<< orphan*/  rxrpc_seq_t ;

/* Variables and functions */

__attribute__((used)) static void rxrpc_input_dup_data(struct rxrpc_call *call, rxrpc_seq_t seq,
				 u8 annotation, bool *_jumbo_bad)
{
	/* Discard normal packets that are duplicates. */
	if (annotation == 0)
		return;

	/* Skip jumbo subpackets that are duplicates.  When we've had three or
	 * more partially duplicate jumbo packets, we refuse to take any more
	 * jumbos for this call.
	 */
	if (!*_jumbo_bad) {
		call->nr_jumbo_bad++;
		*_jumbo_bad = true;
	}
}