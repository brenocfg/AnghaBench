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
struct napi_struct {int (* poll ) (struct napi_struct*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAPI_STATE_NPSVC ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int (*) (struct napi_struct*,int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (struct napi_struct*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_napi_poll (struct napi_struct*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void poll_one_napi(struct napi_struct *napi)
{
	int work;

	/* If we set this bit but see that it has already been set,
	 * that indicates that napi has been disabled and we need
	 * to abort this operation
	 */
	if (test_and_set_bit(NAPI_STATE_NPSVC, &napi->state))
		return;

	/* We explicilty pass the polling call a budget of 0 to
	 * indicate that we are clearing the Tx path only.
	 */
	work = napi->poll(napi, 0);
	WARN_ONCE(work, "%pS exceeded budget in poll\n", napi->poll);
	trace_napi_poll(napi, work, 0);

	clear_bit(NAPI_STATE_NPSVC, &napi->state);
}