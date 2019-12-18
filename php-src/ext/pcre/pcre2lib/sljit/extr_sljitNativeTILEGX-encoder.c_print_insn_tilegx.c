#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ tilegx_mnemonic ;
struct tilegx_operand {int type; } ;
struct tilegx_opcode {scalar_t__ mnemonic; char* name; int num_operands; int /*<<< orphan*/  can_bundle; } ;
struct tilegx_decoded_instruction {unsigned long long* operand_values; struct tilegx_operand** operands; struct tilegx_opcode* opcode; } ;

/* Variables and functions */
 int TILEGX_BUNDLE_SIZE_IN_BYTES ; 
 int TILEGX_MAX_INSTRUCTIONS_PER_BUNDLE ; 
 scalar_t__ TILEGX_OPC_FNOP ; 
 scalar_t__ TILEGX_OPC_NOP ; 
#define  TILEGX_OP_TYPE_ADDRESS 131 
#define  TILEGX_OP_TYPE_IMMEDIATE 130 
#define  TILEGX_OP_TYPE_REGISTER 129 
#define  TILEGX_OP_TYPE_SPR 128 
 int /*<<< orphan*/  abort () ; 
 char* get_tilegx_spr_name (unsigned long long) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int parse_insn_tilegx (unsigned long long,unsigned long long,struct tilegx_decoded_instruction*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char** tilegx_register_names ; 

int
print_insn_tilegx (unsigned char * memaddr)
{
  struct tilegx_decoded_instruction
    decoded[TILEGX_MAX_INSTRUCTIONS_PER_BUNDLE];
  unsigned char opbuf[TILEGX_BUNDLE_SIZE_IN_BYTES];
  int i, num_instructions, num_printed;
  tilegx_mnemonic padding_mnemonic;

  memcpy((void *)opbuf, (void *)memaddr, TILEGX_BUNDLE_SIZE_IN_BYTES);

  /* Parse the instructions in the bundle. */
  num_instructions =
    parse_insn_tilegx (*(unsigned long long *)opbuf, (unsigned long long)memaddr, decoded);

  /* Print the instructions in the bundle. */
  printf("{ ");
  num_printed = 0;

  /* Determine which nop opcode is used for padding and should be skipped. */
  padding_mnemonic = TILEGX_OPC_FNOP;
  for (i = 0; i < num_instructions; i++)
  {
    if (!decoded[i].opcode->can_bundle)
    {
      /* Instructions that cannot be bundled are padded out with nops,
         rather than fnops. Displaying them is always clutter. */
      padding_mnemonic = TILEGX_OPC_NOP;
      break;
    }
  }

  for (i = 0; i < num_instructions; i++)
  {
    const struct tilegx_opcode *opcode = decoded[i].opcode;
    const char *name;
    int j;

    /* Do not print out fnops, unless everything is an fnop, in
       which case we will print out just the last one. */
    if (opcode->mnemonic == padding_mnemonic
        && (num_printed > 0 || i + 1 < num_instructions))
      continue;

    if (num_printed > 0)
      printf(" ; ");
    ++num_printed;

    name = opcode->name;
    if (name == NULL)
      name = "<invalid>";
    printf("%s", name);

    for (j = 0; j < opcode->num_operands; j++)
    {
      unsigned long long num;
      const struct tilegx_operand *op;
      const char *spr_name;

      if (j > 0)
        printf (",");
      printf (" ");

      num = decoded[i].operand_values[j];

      op = decoded[i].operands[j];
      switch (op->type)
      {
      case TILEGX_OP_TYPE_REGISTER:
        printf ("%s", tilegx_register_names[(int)num]);
        break;
      case TILEGX_OP_TYPE_SPR:
        spr_name = get_tilegx_spr_name(num);
        if (spr_name != NULL)
          printf ("%s", spr_name);
        else
          printf ("%d", (int)num);
        break;
      case TILEGX_OP_TYPE_IMMEDIATE:
        printf ("%d", (int)num);
        break;
      case TILEGX_OP_TYPE_ADDRESS:
        printf ("0x%016llx", num);
        break;
      default:
        abort ();
      }
    }
  }
  printf (" }\n");

  return TILEGX_BUNDLE_SIZE_IN_BYTES;
}