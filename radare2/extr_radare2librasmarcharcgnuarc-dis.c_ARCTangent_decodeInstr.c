#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct arcDisState {size_t* instrBuffer; size_t* operandBuffer; int instructionLen; scalar_t__* addresses; int /*<<< orphan*/  instName; int /*<<< orphan*/  condCodeName; int /*<<< orphan*/  auxRegName; int /*<<< orphan*/  coreRegName; struct arcDisState* _this; void** words; } ;
typedef  int /*<<< orphan*/  (* fprintf_ftype ) (void*,char*,size_t*) ;
struct TYPE_7__ {int (* read_memory_func ) (scalar_t__,int /*<<< orphan*/ *,int,TYPE_1__*) ;scalar_t__ endian; int /*<<< orphan*/  (* print_address_func ) (scalar_t__,TYPE_1__*) ;int /*<<< orphan*/  (* memory_error_func ) (int,scalar_t__,TYPE_1__*) ;int /*<<< orphan*/  (* fprintf_func ) (void*,char*,size_t*) ;void* stream; } ;
typedef  TYPE_1__ disassemble_info ;
typedef  scalar_t__ bfd_vma ;
typedef  int /*<<< orphan*/  bfd_byte ;

/* Variables and functions */
 scalar_t__ BFD_ENDIAN_LITTLE ; 
 scalar_t__ __TRANSLATION_REQUIRED (struct arcDisState) ; 
 int /*<<< orphan*/  _auxRegName ; 
 int /*<<< orphan*/  _condCodeName ; 
 int /*<<< orphan*/  _coreRegName ; 
 int /*<<< orphan*/  _instName ; 
 void* bfd_getb32 (int /*<<< orphan*/ *) ; 
 void* bfd_getl32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsmOneArcInst (scalar_t__,void*) ; 
 int /*<<< orphan*/  memset (struct arcDisState*,int /*<<< orphan*/ ,int) ; 
 int stub1 (scalar_t__,int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (int,scalar_t__,TYPE_1__*) ; 
 int stub3 (scalar_t__,int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int /*<<< orphan*/  stub4 (void*,char*,size_t*) ; 
 int /*<<< orphan*/  stub5 (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  stub6 (void*,char*,size_t*) ; 

int
ARCTangent_decodeInstr (bfd_vma address, disassemble_info *info)
{
  int status;
  bfd_byte buffer[4];
  struct arcDisState s;		/* ARC Disassembler state.  */
  void *stream = info->stream; 	/* Output stream.  */
  fprintf_ftype func = info->fprintf_func;

  memset (&s, 0, sizeof(struct arcDisState));

  /* Read first instruction.  */
  status = (*info->read_memory_func) (address, buffer, 4, info);
  if (status != 0)
    {
      (*info->memory_error_func) (status, address, info);
      return -1;
    }
    if (info->endian == BFD_ENDIAN_LITTLE) {
	    s.words[0] = bfd_getl32 (buffer);
    } else {
	    s.words[0] = bfd_getb32 (buffer);
    }
    /* Always read second word in case of limm.  */
    /* We ignore the result since last insn may not have a limm.  */
    status = (*info->read_memory_func) (address + 4, buffer, 4, info);
    if (info->endian == BFD_ENDIAN_LITTLE) {
	    s.words[1] = bfd_getl32 (buffer);
    } else {
	    s.words[1] = bfd_getb32 (buffer);
    }

    s._this = &s;
    s.coreRegName = _coreRegName;
    s.auxRegName = _auxRegName;
    s.condCodeName = _condCodeName;
    s.instName = _instName;

    /* Disassemble.  */
    dsmOneArcInst (address, (void *)&s);

    /* Display the disassembly instruction.  */
    /*
  (*func) (stream, "%08lx ", s.words[0]);
  (*func) (stream, "  ");
*/
    (*func) (stream, "%s ", s.instrBuffer);

    if (__TRANSLATION_REQUIRED (s)) {
	    bfd_vma addr = s.addresses[s.operandBuffer[1] - '0'];

	    (*info->print_address_func) ((bfd_vma)addr, info);
	    //(*func) (stream, "\n");
    } else {
	    (*func) (stream, "%s", s.operandBuffer);
    }

    return s.instructionLen;

}