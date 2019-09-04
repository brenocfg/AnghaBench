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
struct TYPE_2__ {scalar_t__ is_valid; } ;
struct il_priv {int /*<<< orphan*/  restart; int /*<<< orphan*/  workqueue; TYPE_1__ card_alive_init; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_INFO (char*) ; 
 scalar_t__ UCODE_VALID_OK ; 
 scalar_t__ il3945_set_ucode_ptrs (struct il_priv*) ; 
 scalar_t__ il3945_verify_ucode (struct il_priv*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
il3945_init_alive_start(struct il_priv *il)
{
	/* Check alive response for "valid" sign from uCode */
	if (il->card_alive_init.is_valid != UCODE_VALID_OK) {
		/* We had an error bringing up the hardware, so take it
		 * all the way back down so we can try again */
		D_INFO("Initialize Alive failed.\n");
		goto restart;
	}

	/* Bootstrap uCode has loaded initialize uCode ... verify inst image.
	 * This is a paranoid check, because we would not have gotten the
	 * "initialize" alive if code weren't properly loaded.  */
	if (il3945_verify_ucode(il)) {
		/* Runtime instruction load was bad;
		 * take it all the way back down so we can try again */
		D_INFO("Bad \"initialize\" uCode load.\n");
		goto restart;
	}

	/* Send pointers to protocol/runtime uCode image ... init code will
	 * load and launch runtime uCode, which will send us another "Alive"
	 * notification. */
	D_INFO("Initialization Alive received.\n");
	if (il3945_set_ucode_ptrs(il)) {
		/* Runtime instruction load won't happen;
		 * take it all the way back down so we can try again */
		D_INFO("Couldn't set up uCode pointers.\n");
		goto restart;
	}
	return;

restart:
	queue_work(il->workqueue, &il->restart);
}