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
struct smc_connection {int /*<<< orphan*/  splice_pending; int /*<<< orphan*/  bytes_to_rcv; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int smc_rx_data_available_and_no_splice_pend(struct smc_connection *conn)
{
	return atomic_read(&conn->bytes_to_rcv) &&
	       !atomic_read(&conn->splice_pending);
}