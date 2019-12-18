#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nios2_opcode {int pinfo; unsigned int match; char* name; } ;
struct TYPE_4__ {struct TYPE_4__* next; struct nios2_opcode const* opcode; } ;
typedef  TYPE_1__ nios2_opcode_hash ;

/* Variables and functions */
 int NIOS2_INSN_MACRO ; 
 int NIOS2_INSN_MACRO_MOV ; 
 int NIOS2_INSN_MACRO_MOVI ; 
 size_t NUMOPCODES ; 
 unsigned int OP_MASK_OP ; 
 unsigned int OP_SH_OP ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ malloc (int) ; 
 TYPE_1__** nios2_hash ; 
 int nios2_hash_init ; 
 struct nios2_opcode const* nios2_opcodes ; 
 TYPE_1__** nios2_ps_hash ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
nios2_init_opcode_hash (void)
{
  unsigned int i;
  register const struct nios2_opcode *op;

  for (i = 0; i <= OP_MASK_OP; ++i) {
	  nios2_hash[0] = NULL;
  }
  for (i = 0; i <= OP_MASK_OP; i++) {
	  for (op = nios2_opcodes; op < &nios2_opcodes[NUMOPCODES]; op++) {
		  nios2_opcode_hash *new_hash;
		  nios2_opcode_hash **bucket = NULL;

		  if ((op->pinfo & NIOS2_INSN_MACRO) == NIOS2_INSN_MACRO) {
			  if (i == ((op->match >> OP_SH_OP) & OP_MASK_OP) && (op->pinfo & (NIOS2_INSN_MACRO_MOV | NIOS2_INSN_MACRO_MOVI) & 0x7fffffff)) {
				  bucket = &(nios2_ps_hash[i]);
			  }
		  } else if (i == ((op->match >> OP_SH_OP) & OP_MASK_OP)) {
			  bucket = &(nios2_hash[i]);
		  }

		  if (bucket) {
			  new_hash =
				  (nios2_opcode_hash *)malloc (sizeof (nios2_opcode_hash));
			  if (!new_hash) {
				  fprintf (stderr,
					  "error allocating memory...broken disassembler\n");
				  abort ();
			  }
			  new_hash->opcode = op;
			  new_hash->next = NULL;
			  while (*bucket) {
				  bucket = &((*bucket)->next);
			  }
			  *bucket = new_hash;
		  }
	  }
  }
  nios2_hash_init = 1;
#ifdef DEBUG_HASHTABLE
  for (i = 0; i <= OP_MASK_OP; ++i)
    {
      nios2_opcode_hash *tmp_hash = nios2_hash[i];
      printf ("index: 0x%02X	ops: ", i);
      while (tmp_hash != NULL)
	{
	  printf ("%s ", tmp_hash->opcode->name);
	  tmp_hash = tmp_hash->next;
	}
      printf ("\n");
    }

  for (i = 0; i <= OP_MASK_OP; ++i)
    {
      nios2_opcode_hash *tmp_hash = nios2_ps_hash[i];
      printf ("index: 0x%02X	ops: ", i);
      while (tmp_hash != NULL)
	{
	  printf ("%s ", tmp_hash->opcode->name);
	  tmp_hash = tmp_hash->next;
	}
      printf ("\n");
    }
#endif /* DEBUG_HASHTABLE */
}