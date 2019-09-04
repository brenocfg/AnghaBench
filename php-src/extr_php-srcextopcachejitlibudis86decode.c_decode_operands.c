#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ud {TYPE_5__* itab_entry; TYPE_6__* operand; } ;
struct TYPE_12__ {scalar_t__ type; } ;
struct TYPE_10__ {int /*<<< orphan*/  size; int /*<<< orphan*/  type; } ;
struct TYPE_9__ {int /*<<< orphan*/  size; int /*<<< orphan*/  type; } ;
struct TYPE_8__ {int /*<<< orphan*/  size; int /*<<< orphan*/  type; } ;
struct TYPE_7__ {int /*<<< orphan*/  size; int /*<<< orphan*/  type; } ;
struct TYPE_11__ {TYPE_4__ operand4; TYPE_3__ operand3; TYPE_2__ operand2; TYPE_1__ operand1; } ;

/* Variables and functions */
 scalar_t__ UD_NONE ; 
 int /*<<< orphan*/  decode_operand (struct ud*,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
decode_operands(struct ud* u)
{
  decode_operand(u, &u->operand[0],
                    u->itab_entry->operand1.type,
                    u->itab_entry->operand1.size);
  if (u->operand[0].type != UD_NONE) {
      decode_operand(u, &u->operand[1],
                        u->itab_entry->operand2.type,
                        u->itab_entry->operand2.size);
  }
  if (u->operand[1].type != UD_NONE) {
      decode_operand(u, &u->operand[2],
                        u->itab_entry->operand3.type,
                        u->itab_entry->operand3.size);
  }
  if (u->operand[2].type != UD_NONE) {
      decode_operand(u, &u->operand[3],
                        u->itab_entry->operand4.type,
                        u->itab_entry->operand4.size);
  }
  return 0;
}