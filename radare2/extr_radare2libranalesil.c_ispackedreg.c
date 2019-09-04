#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* anal; } ;
struct TYPE_7__ {scalar_t__ packed_size; } ;
struct TYPE_6__ {int /*<<< orphan*/  reg; } ;
typedef  TYPE_2__ RRegItem ;
typedef  TYPE_3__ RAnalEsil ;

/* Variables and functions */
 TYPE_2__* r_reg_get (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static bool ispackedreg(RAnalEsil *esil, const char *str) {
	RRegItem *ri = r_reg_get (esil->anal->reg, str, -1);
	return ri? ri->packed_size > 0: false;
}