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

/* Variables and functions */
 int /*<<< orphan*/  sid_free ; 
 int /*<<< orphan*/ * sig_app ; 
 int /*<<< orphan*/ * sigx_app ; 
 int /*<<< orphan*/  sk_nid_triple_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_nid_triple_pop_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void OBJ_sigid_free(void)
{
    sk_nid_triple_pop_free(sig_app, sid_free);
    sig_app = NULL;
    sk_nid_triple_free(sigx_app);
    sigx_app = NULL;
}