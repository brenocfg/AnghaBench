#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  io_ptr; int /*<<< orphan*/  tlist_cache; int /*<<< orphan*/  plist_cache; } ;
typedef  TYPE_1__ WindCtx ;

/* Variables and functions */
 int /*<<< orphan*/  R_FREE (TYPE_1__*) ; 
 int /*<<< orphan*/  iob_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_list_free (int /*<<< orphan*/ ) ; 

void windbg_ctx_free(WindCtx **ctx) {
	if (!ctx || !*ctx) {
		return;
	}
	r_list_free ((*ctx)->plist_cache);
	r_list_free ((*ctx)->tlist_cache);
	iob_close ((*ctx)->io_ptr);
	R_FREE (*ctx);
}