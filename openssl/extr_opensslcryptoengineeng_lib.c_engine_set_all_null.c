#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ flags; int /*<<< orphan*/ * cmd_defns; int /*<<< orphan*/ * load_pubkey; int /*<<< orphan*/ * load_privkey; int /*<<< orphan*/ * ctrl; int /*<<< orphan*/ * finish; int /*<<< orphan*/ * init; int /*<<< orphan*/ * destroy; int /*<<< orphan*/ * digests; int /*<<< orphan*/ * ciphers; int /*<<< orphan*/ * rand_meth; int /*<<< orphan*/ * dh_meth; int /*<<< orphan*/ * dsa_meth; int /*<<< orphan*/ * rsa_meth; int /*<<< orphan*/ * name; int /*<<< orphan*/ * id; } ;
typedef  TYPE_1__ ENGINE ;

/* Variables and functions */

void engine_set_all_null(ENGINE *e)
{
    e->id = NULL;
    e->name = NULL;
    e->rsa_meth = NULL;
    e->dsa_meth = NULL;
    e->dh_meth = NULL;
    e->rand_meth = NULL;
    e->ciphers = NULL;
    e->digests = NULL;
    e->destroy = NULL;
    e->init = NULL;
    e->finish = NULL;
    e->ctrl = NULL;
    e->load_privkey = NULL;
    e->load_pubkey = NULL;
    e->cmd_defns = NULL;
    e->flags = 0;
}