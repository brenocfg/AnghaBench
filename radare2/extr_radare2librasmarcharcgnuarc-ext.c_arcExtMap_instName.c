#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ExtInstruction {int major; unsigned char minor; int flags; char const* name; struct ExtInstruction* next; } ;
struct TYPE_2__ {struct ExtInstruction** instructions; } ;

/* Variables and functions */
 int E_ARC_MACH_A4 ; 
 size_t INST_HASH (int,unsigned char) ; 
 int /*<<< orphan*/  M ; 
 int P ; 
 TYPE_1__ arc_extension_map ; 

const char *
arcExtMap_instName (int opcode, int insn, int *flags)
{
  /* Here the following tasks need to be done.  First of all, the opcode
     stored in the Extension Map is the real opcode.  However, the subopcode
     stored in the instruction to be disassembled is mangled.  We pass (in
     minor opcode), the instruction word.  Here we will un-mangle it and get
     the real subopcode which we can look for in the Extension Map.  This
     function is used both for the ARCTangent and the ARCompact, so we would
     also need some sort of a way to distinguish between the two
     architectures.  This is because the ARCTangent does not do any of this
     mangling so we have no issues there.  */

  /* If P[22:23] is 0 or 2 then un-mangle using iiiiiI.  If it is 1 then use
     iiiiIi.  Now, if P is 3 then check M[5:5] and if it is 0 then un-mangle
     using iiiiiI else iiiiii.  */

  unsigned char minor;
  struct ExtInstruction *temp;

  if (*flags != E_ARC_MACH_A4) /* ARCompact extension instructions.  */
    {
      /* 16-bit instructions.  */
      if (0x08 <= opcode && opcode <= 0x0b)
	{
	  /* I - set but not used */
	  unsigned char /* I, */ b, c, i;

	  /* I = (insn & 0xf800) >> 11; */
	  b = (insn & 0x0700) >> 8;
	  c = (insn & 0x00e0) >> 5;
	  i = (insn & 0x001f);

	  if (i) {
		  minor = i;
	  } else {
		  minor = (c == 0x07) ? b : c;
	  }
	}
      /* 32-bit instructions.  */
      else
	{
	  /* P, M - set but not used */
	  unsigned char /* P, M, */ I, A, B;

	  /* P = (insn & 0x00c00000) >> 22; */
	  /* M = (insn & 0x00000020); */
	  I = (insn & 0x003f0000) >> 16;
	  A = (insn & 0x0000003f);
	  B = ((insn & 0x07000000) >> 24) | ((insn & 0x00007000) >> 9);

	  if (I != 0x2f)
	    {
#ifndef UNMANGLED
	      switch (P)
		{
		case 3:
		  if (M)
		    {
		      minor = I;
		      break;
		    }
		case 0:
		case 2:
		  minor = (I >> 1) | ((I & 0x1) << 5);
		  break;
		case 1:
		  minor = (I >> 1) | (I & 0x1) | ((I & 0x2) << 4);
		}
#else
	      minor = I;
#endif
	    }
	  else
	    {
		    if (A != 0x3f) {
			    minor = A;
		    } else {
			    minor = B;
		    }
	    }
	}
  } else { /* ARCTangent extension instructions.  */
	  minor = insn;
  }

  temp = arc_extension_map.instructions[INST_HASH (opcode, minor)];
  while (temp)
    {
      if ((temp->major == opcode) && (temp->minor == minor))
	{
	  *flags = temp->flags;
	  return temp->name;
	}
      temp = temp->next;
    }

  return NULL;
}