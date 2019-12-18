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
typedef  scalar_t__ xtensa_opcode ;
struct TYPE_8__ {TYPE_2__* slots; TYPE_1__* formats; } ;
typedef  TYPE_3__ xtensa_isa_internal ;
typedef  scalar_t__ xtensa_isa ;
typedef  int /*<<< orphan*/  xtensa_insnbuf ;
typedef  size_t xtensa_format ;
struct TYPE_7__ {scalar_t__ (* opcode_decode_fn ) (int /*<<< orphan*/  const) ;} ;
struct TYPE_6__ {int* slot_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FORMAT (TYPE_3__*,size_t,scalar_t__) ; 
 int /*<<< orphan*/  CHECK_SLOT (TYPE_3__*,size_t,int,scalar_t__) ; 
 scalar_t__ XTENSA_UNDEFINED ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  xtensa_isa_bad_opcode ; 
 int /*<<< orphan*/  xtisa_errno ; 
 int /*<<< orphan*/  xtisa_error_msg ; 

xtensa_opcode
xtensa_opcode_decode (xtensa_isa isa, xtensa_format fmt, int slot,
		      const xtensa_insnbuf slotbuf)
{
  xtensa_isa_internal *intisa = (xtensa_isa_internal *) isa;
  int slot_id;
  xtensa_opcode opc;

  CHECK_FORMAT (intisa, fmt, XTENSA_UNDEFINED);
  CHECK_SLOT (intisa, fmt, slot, XTENSA_UNDEFINED);

  slot_id = intisa->formats[fmt].slot_id[slot];

  opc = (intisa->slots[slot_id].opcode_decode_fn) (slotbuf);
  if (opc != XTENSA_UNDEFINED) {
	  return opc;
  }

  xtisa_errno = xtensa_isa_bad_opcode;
  strcpy (xtisa_error_msg, "cannot decode opcode");
  return XTENSA_UNDEFINED;
}