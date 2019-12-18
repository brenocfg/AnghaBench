#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct arcDisState {int instructionLen; int* words; int /*<<< orphan*/  instName; int /*<<< orphan*/  condCodeName; int /*<<< orphan*/  auxRegName; int /*<<< orphan*/  coreRegName; struct arcDisState* _this; } ;
struct TYPE_10__ {scalar_t__ endian; int (* read_memory_func ) (scalar_t__,int*,int,TYPE_1__*) ;int bytes_per_line; int /*<<< orphan*/  (* memory_error_func ) (int,scalar_t__,TYPE_1__*) ;} ;
typedef  TYPE_1__ disassemble_info ;
typedef  scalar_t__ bfd_vma ;
typedef  int bfd_byte ;

/* Variables and functions */
 scalar_t__ BFD_ENDIAN_LITTLE ; 
 int /*<<< orphan*/  _auxRegName ; 
 int /*<<< orphan*/  _condCodeName ; 
 int /*<<< orphan*/  _coreRegName ; 
 int /*<<< orphan*/  _instName ; 
 void* bfd_getb32 (int*) ; 
 void* bfd_getl32 (int*) ; 
 int dsmOneArcInst (scalar_t__,void*,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (struct arcDisState*,int /*<<< orphan*/ ,int) ; 
 int stub1 (scalar_t__,int*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (int,scalar_t__,TYPE_1__*) ; 
 int stub3 (scalar_t__,int*,int,TYPE_1__*) ; 
 int stub4 (scalar_t__,int*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  stub5 (int,scalar_t__,TYPE_1__*) ; 
 int stub6 (scalar_t__,int*,int,TYPE_1__*) ; 

struct arcDisState
arcAnalyzeInstr
(
 bfd_vma           address,		/* Address of this instruction */
 disassemble_info* info
 )
{
  int status;
  bfd_byte buffer[4];
  struct arcDisState s;	/* ARC Disassembler state */
  int bytes;
  int lowbyte, highbyte;

  lowbyte = ((info->endian == BFD_ENDIAN_LITTLE) ? 1 : 0);
  highbyte = ((info->endian == BFD_ENDIAN_LITTLE) ? 0 : 1);

  memset(&s, 0, sizeof(struct arcDisState));

  /* read first instruction */
  status = (*info->read_memory_func) (address, buffer, 2, info);

  if (status != 0)
    {
      (*info->memory_error_func) (status, address, info);
      s.instructionLen = -1;
      return s;
    }

  if (((buffer[lowbyte] & 0xf8) > 0x38) && ((buffer[lowbyte] & 0xf8) != 0x48))
  {
    s.instructionLen = 2;
    s.words[0] = (buffer[lowbyte] << 8) | buffer[highbyte];
    status = (*info->read_memory_func) (address + 2, buffer, 4, info);
    if (info->endian == BFD_ENDIAN_LITTLE) {
	    s.words[1] = bfd_getl32 (buffer);
    } else {
	    s.words[1] = bfd_getb32 (buffer);
    }
  }
  else
  {
    s.instructionLen = 4;
    status = (*info->read_memory_func) (address + 2, &buffer[2], 2, info);
    if (status != 0)
    {
      (*info->memory_error_func) (status, address + 2, info);
      s.instructionLen = -1;
      return s;
    }
    if (info->endian == BFD_ENDIAN_LITTLE) {
	    s.words[0] = bfd_getl32 (buffer);
    } else {
	    s.words[0] = bfd_getb32 (buffer);
    }

    /* always read second word in case of limm */
    /* we ignore the result since last insn may not have a limm */
    status = (*info->read_memory_func) (address + 4, buffer, 4, info);
    if (info->endian == BFD_ENDIAN_LITTLE) {
	    s.words[1] = bfd_getl32 (buffer);
    } else {
	    s.words[1] = bfd_getb32 (buffer);
    }
  }

  s._this = &s;
  s.coreRegName = _coreRegName;
  s.auxRegName = _auxRegName;
  s.condCodeName = _condCodeName;
  s.instName = _instName;

  /* disassemble */
  bytes = dsmOneArcInst(address, (void *)&s, info);
  /* We print max bytes for instruction */
  info->bytes_per_line = bytes;
  return s;
}