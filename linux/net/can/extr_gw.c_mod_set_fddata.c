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
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
struct TYPE_4__ {TYPE_1__ set; } ;
struct cf_mod {TYPE_2__ modframe; } ;
struct canfd_frame {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CANFD_MAX_DLEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mod_set_fddata(struct canfd_frame *cf, struct cf_mod *mod)
{
	memcpy(cf->data, mod->modframe.set.data, CANFD_MAX_DLEN);
}