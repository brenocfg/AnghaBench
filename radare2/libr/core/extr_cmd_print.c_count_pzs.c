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
struct count_pz_t {scalar_t__ flagspace; scalar_t__ addr; scalar_t__ size; int /*<<< orphan*/ * ret; } ;
struct TYPE_3__ {scalar_t__ space; scalar_t__ offset; scalar_t__ size; } ;
typedef  TYPE_1__ RFlagItem ;

/* Variables and functions */

__attribute__((used)) static bool count_pzs(RFlagItem *fi, void *u) {
	struct count_pz_t *user = (struct count_pz_t *)u;
	if (fi->space == user->flagspace &&
	    ((user->addr <= fi->offset && fi->offset < user->addr + user->size) ||
	     (user->addr <= fi->offset + fi->size && fi->offset + fi->size < user->addr + user->size))) {
		(*user->ret)++;
	}

	return true;
}