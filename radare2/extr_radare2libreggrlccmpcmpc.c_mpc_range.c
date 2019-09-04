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
struct TYPE_8__ {char x; char y; } ;
struct TYPE_9__ {TYPE_1__ range; } ;
struct TYPE_10__ {TYPE_2__ data; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ mpc_parser_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPC_TYPE_RANGE ; 
 TYPE_3__* mpc_expectf (TYPE_3__*,char*,char,char) ; 
 TYPE_3__* mpc_undefined () ; 

mpc_parser_t *mpc_range(char s, char e) {
  mpc_parser_t *p = mpc_undefined();
  p->type = MPC_TYPE_RANGE;
  p->data.range.x = s;
  p->data.range.y = e;
  return mpc_expectf(p, "character between '%c' and '%c'", s, e);
}