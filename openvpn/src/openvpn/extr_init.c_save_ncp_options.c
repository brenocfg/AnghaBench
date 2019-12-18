#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  keysize; int /*<<< orphan*/  authname; int /*<<< orphan*/  ciphername; } ;
struct TYPE_3__ {int /*<<< orphan*/  keysize; int /*<<< orphan*/  authname; int /*<<< orphan*/  ciphername; } ;
struct context {TYPE_2__ options; TYPE_1__ c1; } ;

/* Variables and functions */

__attribute__((used)) static void
save_ncp_options(struct context *c)
{
    c->c1.ciphername = c->options.ciphername;
    c->c1.authname = c->options.authname;
    c->c1.keysize = c->options.keysize;
}