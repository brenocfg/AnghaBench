#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  f; TYPE_2__* (* get_at ) (int /*<<< orphan*/ ,scalar_t__,int) ;} ;
struct TYPE_11__ {TYPE_1__ flb; } ;
struct TYPE_10__ {scalar_t__ size; scalar_t__ addr; } ;
struct TYPE_9__ {scalar_t__ name; } ;
typedef  TYPE_2__ RFlagItem ;
typedef  TYPE_3__ RAnalOp ;
typedef  TYPE_4__ RAnal ;

/* Variables and functions */
 int /*<<< orphan*/  r_return_val_if_fail (int /*<<< orphan*/ ,int) ; 
 scalar_t__ strstr (scalar_t__,char*) ; 
 TYPE_2__* stub1 (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static bool isSymbolNextInstruction(RAnal *anal, RAnalOp *op) {
	r_return_val_if_fail (anal && op && anal->flb.get_at, false);

	RFlagItem *fi = anal->flb.get_at (anal->flb.f, op->addr + op->size, false);
	return (fi && fi->name && (strstr (fi->name, "imp.") || strstr (fi->name, "sym.")
			|| strstr (fi->name, "entry") || strstr (fi->name, "main")));
}