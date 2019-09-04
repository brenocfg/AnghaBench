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
struct il_priv {int /*<<< orphan*/  restart; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  temperature; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_INFO (char*) ; 
 int /*<<< orphan*/  il4965_hw_get_temperature (struct il_priv*) ; 
 scalar_t__ il4965_set_ucode_ptrs (struct il_priv*) ; 
 scalar_t__ il4965_verify_ucode (struct il_priv*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
il4965_init_alive_start(struct il_priv *il)
{
	/* Bootstrap uCode has loaded initialize uCode ... verify inst image.
	 * This is a paranoid check, because we would not have gotten the
	 * "initialize" alive if code weren't properly loaded.  */
	if (il4965_verify_ucode(il)) {
		/* Runtime instruction load was bad;
		 * take it all the way back down so we can try again */
		D_INFO("Bad \"initialize\" uCode load.\n");
		goto restart;
	}

	/* Calculate temperature */
	il->temperature = il4965_hw_get_temperature(il);

	/* Send pointers to protocol/runtime uCode image ... init code will
	 * load and launch runtime uCode, which will send us another "Alive"
	 * notification. */
	D_INFO("Initialization Alive received.\n");
	if (il4965_set_ucode_ptrs(il)) {
		/* Runtime instruction load won't happen;
		 * take it all the way back down so we can try again */
		D_INFO("Couldn't set up uCode pointers.\n");
		goto restart;
	}
	return;

restart:
	queue_work(il->workqueue, &il->restart);
}