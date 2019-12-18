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
struct TYPE_8__ {TYPE_2__* slots; TYPE_1__* formats; } ;
typedef  TYPE_3__ xtensa_isa_internal ;
typedef  scalar_t__ xtensa_isa ;
typedef  int /*<<< orphan*/  xtensa_insnbuf ;
typedef  size_t xtensa_format ;
struct TYPE_7__ {int /*<<< orphan*/  (* get_fn ) (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {int* slot_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FORMAT (TYPE_3__*,size_t,int) ; 
 int /*<<< orphan*/  CHECK_SLOT (TYPE_3__*,size_t,int,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 

int
xtensa_format_get_slot (xtensa_isa isa, xtensa_format fmt, int slot,
			const xtensa_insnbuf insn, xtensa_insnbuf slotbuf)
{
  xtensa_isa_internal *intisa = (xtensa_isa_internal *) isa;
  int slot_id;

  CHECK_FORMAT (intisa, fmt, -1);
  CHECK_SLOT (intisa, fmt, slot, -1);

  slot_id = intisa->formats[fmt].slot_id[slot];
  (*intisa->slots[slot_id].get_fn) (insn, slotbuf);
  return 0;
}