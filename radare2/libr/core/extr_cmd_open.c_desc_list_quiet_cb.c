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
typedef  int /*<<< orphan*/  ut32 ;
struct TYPE_4__ {int /*<<< orphan*/  fd; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* cb_printf ) (char*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ RPrint ;
typedef  TYPE_2__ RIODesc ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool desc_list_quiet_cb(void *user, void *data, ut32 id) {
	RPrint *p = (RPrint *)user;
	RIODesc *desc = (RIODesc *)data;
	p->cb_printf ("%d\n", desc->fd);
	return true;
}