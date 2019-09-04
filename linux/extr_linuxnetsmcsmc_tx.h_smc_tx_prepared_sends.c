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
typedef  union smc_host_cursor {int dummy; } smc_host_cursor ;
struct smc_connection {TYPE_1__* sndbuf_desc; int /*<<< orphan*/  tx_curs_prep; int /*<<< orphan*/  tx_curs_sent; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  smc_curs_copy (union smc_host_cursor*,int /*<<< orphan*/ *,struct smc_connection*) ; 
 int smc_curs_diff (int /*<<< orphan*/ ,union smc_host_cursor*,union smc_host_cursor*) ; 

__attribute__((used)) static inline int smc_tx_prepared_sends(struct smc_connection *conn)
{
	union smc_host_cursor sent, prep;

	smc_curs_copy(&sent, &conn->tx_curs_sent, conn);
	smc_curs_copy(&prep, &conn->tx_curs_prep, conn);
	return smc_curs_diff(conn->sndbuf_desc->len, &sent, &prep);
}