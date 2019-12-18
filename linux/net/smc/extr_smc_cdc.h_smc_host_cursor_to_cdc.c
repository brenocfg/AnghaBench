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
union smc_host_cursor {int /*<<< orphan*/  wrap; int /*<<< orphan*/  count; } ;
union smc_cdc_cursor {int /*<<< orphan*/  wrap; int /*<<< orphan*/  count; } ;
struct smc_connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smc_curs_copy (union smc_host_cursor*,union smc_host_cursor*,struct smc_connection*) ; 

__attribute__((used)) static inline void smc_host_cursor_to_cdc(union smc_cdc_cursor *peer,
					  union smc_host_cursor *local,
					  union smc_host_cursor *save,
					  struct smc_connection *conn)
{
	smc_curs_copy(save, local, conn);
	peer->count = htonl(save->count);
	peer->wrap = htons(save->wrap);
	/* peer->reserved = htons(0); must be ensured by caller */
}