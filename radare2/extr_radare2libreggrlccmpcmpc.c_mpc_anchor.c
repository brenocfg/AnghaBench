#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int (* f ) (char,char) ;} ;
struct TYPE_9__ {TYPE_1__ anchor; } ;
struct TYPE_10__ {TYPE_2__ data; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ mpc_parser_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPC_TYPE_ANCHOR ; 
 TYPE_3__* mpc_expect (TYPE_3__*,char*) ; 
 TYPE_3__* mpc_undefined () ; 

mpc_parser_t *mpc_anchor(int(*f)(char,char)) {
  mpc_parser_t *p = mpc_undefined();
  p->type = MPC_TYPE_ANCHOR;
  p->data.anchor.f = f;
  return mpc_expect(p, "anchor");
}