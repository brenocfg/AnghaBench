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
union smc_host_cursor {scalar_t__ count; scalar_t__ wrap; } ;
union smc_cdc_cursor {int /*<<< orphan*/  wrap; int /*<<< orphan*/  count; } ;
struct smc_connection {int dummy; } ;

/* Variables and functions */
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smc_curs_copy (union smc_host_cursor*,union smc_host_cursor*,struct smc_connection*) ; 
 int /*<<< orphan*/  smc_curs_copy_net (union smc_cdc_cursor*,union smc_cdc_cursor*,struct smc_connection*) ; 

__attribute__((used)) static inline void smc_cdc_cursor_to_host(union smc_host_cursor *local,
					  union smc_cdc_cursor *peer,
					  struct smc_connection *conn)
{
	union smc_host_cursor temp, old;
	union smc_cdc_cursor net;

	smc_curs_copy(&old, local, conn);
	smc_curs_copy_net(&net, peer, conn);
	temp.count = ntohl(net.count);
	temp.wrap = ntohs(net.wrap);
	if ((old.wrap > temp.wrap) && temp.wrap)
		return;
	if ((old.wrap == temp.wrap) &&
	    (old.count > temp.count))
		return;
	smc_curs_copy(local, &temp, conn);
}