#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct disassemble_info {int flags; scalar_t__ endian_code; scalar_t__ symtab_size; int symtab_pos; int bytes_per_line; unsigned int bytes_per_chunk; int (* read_memory_func ) (int,int /*<<< orphan*/ *,unsigned int,struct disassemble_info*) ;int /*<<< orphan*/  (* memory_error_func ) (int,int,struct disassemble_info*) ;scalar_t__ display_endian; TYPE_1__** symtab; int /*<<< orphan*/ * section; struct arm_private_data* private_data; int /*<<< orphan*/  mach; int /*<<< orphan*/ * disassembler_options; } ;
struct arm_private_data {int has_mapping_symbols; int last_mapping_sym; int last_type; scalar_t__ last_mapping_addr; int /*<<< orphan*/  features; } ;
typedef  enum map_type { ____Placeholder_map_type } map_type ;
typedef  int bfd_vma ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int bfd_boolean ;
struct TYPE_3__ {int /*<<< orphan*/ * section; } ;

/* Variables and functions */
 scalar_t__ BFD_ENDIAN_BIG ; 
 scalar_t__ BFD_ENDIAN_LITTLE ; 
 int DISASSEMBLE_DATA ; 
 int FALSE ; 
 int INSN_HAS_RELOC ; 
 int MAP_ARM ; 
 int MAP_DATA ; 
 int MAP_THUMB ; 
 int TRUE ; 
 int USER_SPECIFIED_MACHINE_TYPE ; 
 scalar_t__ bfd_asymbol_flavour (TYPE_1__*) ; 
 int bfd_asymbol_value (TYPE_1__*) ; 
 int /*<<< orphan*/  bfd_mach_arm_unknown ; 
 scalar_t__ bfd_target_elf_flavour ; 
 int /*<<< orphan*/  find_ifthen_state (int,struct disassemble_info*,int) ; 
 scalar_t__ force_thumb ; 
 scalar_t__ get_map_sym_type (struct disassemble_info*,int,int*) ; 
 scalar_t__ get_sym_code_type (struct disassemble_info*,int,int*) ; 
 int ifthen_address ; 
 int ifthen_next_state ; 
 int ifthen_state ; 
 scalar_t__ is_mapping_symbol (struct disassemble_info*,int,int*) ; 
 int /*<<< orphan*/  parse_arm_disassembler_options (int /*<<< orphan*/ *) ; 
 void print_insn_arm (int,struct disassemble_info*,long) ; 
 void print_insn_data (int,struct disassemble_info*,long) ; 
 void print_insn_thumb16 (int,struct disassemble_info*,long) ; 
 void print_insn_thumb32 (int,struct disassemble_info*,long) ; 
 int /*<<< orphan*/  select_arm_features (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (int,int /*<<< orphan*/ *,unsigned int,struct disassemble_info*) ; 
 int stub2 (int,int /*<<< orphan*/ *,int,struct disassemble_info*) ; 
 int stub3 (int,int /*<<< orphan*/ *,int,struct disassemble_info*) ; 
 int stub4 (int,int /*<<< orphan*/ *,int,struct disassemble_info*) ; 
 int /*<<< orphan*/  stub5 (int,int,struct disassemble_info*) ; 

__attribute__((used)) static int
print_insn (bfd_vma pc, struct disassemble_info *info, bfd_boolean little)
{
  unsigned char b[4];
  long		given;
  int           status;
  int           is_thumb = FALSE;
  int           is_data = FALSE;
  int           little_code;
  unsigned int	size = 4;
  void	 	(*printer) (bfd_vma, struct disassemble_info *, long);
  bfd_boolean   found = FALSE;
  struct arm_private_data *private_data;

  if (info->disassembler_options)
    {
      parse_arm_disassembler_options (info->disassembler_options);

      /* To avoid repeated parsing of these options, we remove them here.  */
      info->disassembler_options = NULL;
    }

  /* PR 10288: Control which instructions will be disassembled.  */
  if (info->private_data == NULL)
    {
      static struct arm_private_data private;

      if ((info->flags & USER_SPECIFIED_MACHINE_TYPE) == 0) {
	      /* If the user did not use the -m command line switch then default to
	   disassembling all types of ARM instruction.

	   The info->mach value has to be ignored as this will be based on
	   the default archictecture for the target and/or hints in the notes
	   section, but it will never be greater than the current largest arm
	   machine value (iWMMXt2), which is only equivalent to the V5TE
	   architecture.  ARM architectures have advanced beyond the machine
	   value encoding, and these newer architectures would be ignored if
	   the machine value was used.

	   Ie the -m switch is used to restrict which instructions will be
	   disassembled.  If it is necessary to use the -m switch to tell
	   objdump that an ARM binary is being disassembled, eg because the
	   input is a raw binary file, but it is also desired to disassemble
	   all ARM instructions then use "-marm".  This will select the
	   "unknown" arm architecture which is compatible with any ARM
	   instruction.  */
	      info->mach = bfd_mach_arm_unknown;
      }

      /* Compute the architecture bitmask from the machine number.
	 Note: This assumes that the machine number will not change
	 during disassembly....  */
      select_arm_features (info->mach, & private.features);

      private.has_mapping_symbols = -1;
      private.last_mapping_sym = -1;
      private.last_mapping_addr = 0;

      info->private_data = & private;
    }

  private_data = info->private_data;

  /* Decide if our code is going to be little-endian, despite what the
     function argument might say.  */
  little_code = ((info->endian_code == BFD_ENDIAN_LITTLE) || little);

  /* For ELF, consult the symbol table to determine what kind of code
     or data we have.  */
  if (info->symtab_size != 0
      && bfd_asymbol_flavour (*info->symtab) == bfd_target_elf_flavour)
    {
      bfd_vma addr;
      int n, start;
      int last_sym = -1;
      enum map_type type = MAP_ARM;

      /* Start scanning at the start of the function, or wherever
	 we finished last time.  */
      /* PR 14006.  When the address is 0 we are either at the start of the
	 very first function, or else the first function in a new, unlinked
	 executable section (eg because of -ffunction-sections).  Either way
	 start scanning from the beginning of the symbol table, not where we
	 left off last time.  */
      if (pc == 0) {
	      start = 0;
      } else {
	      start = info->symtab_pos + 1;
	      if (start < private_data->last_mapping_sym) {
		      start = private_data->last_mapping_sym;
	      }
	}
      found = FALSE;

      /* First, look for mapping symbols.  */
      if (private_data->has_mapping_symbols != 0)
	{
	  /* Scan up to the location being disassembled.  */
	  for (n = start; n < info->symtab_size; n++)
	    {
	      addr = bfd_asymbol_value (info->symtab[n]);
	      if (addr > pc) {
		      break;
	      }
	      if (get_map_sym_type (info, n, &type))
		{
		  last_sym = n;
		  found = TRUE;
		}
	    }

	  if (!found)
	    {
	      /* No mapping symbol found at this address.  Look backwards
		 for a preceding one.  */
	      for (n = start - 1; n >= 0; n--)
		{
		  if (get_map_sym_type (info, n, &type))
		    {
		      last_sym = n;
		      found = TRUE;
		      break;
		    }
		}
	    }

	    if (found) {
		    private_data->has_mapping_symbols = 1;
	    }

	    /* No mapping symbols were found.  A leading $d may be
	     omitted for sections which start with data; but for
	     compatibility with legacy and stripped binaries, only
	     assume the leading $d if there is at least one mapping
	     symbol in the file.  */
	    if (!found && private_data->has_mapping_symbols == -1) {
		    /* Look for mapping symbols, in any section.  */
		    for (n = 0; n < info->symtab_size; n++) {
			    if (is_mapping_symbol (info, n, &type)) {
				    private_data->has_mapping_symbols = 1;
				    break;
			    }
		    }
		    if (private_data->has_mapping_symbols == -1) {
			    private_data->has_mapping_symbols = 0;
		    }
	    }

	  if (!found && private_data->has_mapping_symbols == 1)
	    {
	      type = MAP_DATA;
	      found = TRUE;
	    }
	}

      /* Next search for function symbols to separate ARM from Thumb
	 in binaries without mapping symbols.  */
      if (!found)
	{
	  /* Scan up to the location being disassembled.  */
	  for (n = start; n < info->symtab_size; n++)
	    {
	      addr = bfd_asymbol_value (info->symtab[n]);
	      if (addr > pc) {
		      break;
	      }
	      if (get_sym_code_type (info, n, &type))
		{
		  last_sym = n;
		  found = TRUE;
		}
	    }

	  if (!found)
	    {
	      /* No mapping symbol found at this address.  Look backwards
		 for a preceding one.  */
	      for (n = start - 1; n >= 0; n--)
		{
		  if (get_sym_code_type (info, n, &type))
		    {
		      last_sym = n;
		      found = TRUE;
		      break;
		    }
		}
	    }
	}

      private_data->last_mapping_sym = last_sym;
      private_data->last_type = type;
      is_thumb = (private_data->last_type == MAP_THUMB);
      is_data = (private_data->last_type == MAP_DATA);

      /* Look a little bit ahead to see if we should print out
	 two or four bytes of data.  If there's a symbol,
	 mapping or otherwise, after two bytes then don't
	 print more.  */
      if (is_data)
	{
	  size = 4 - (pc & 3);
	  for (n = last_sym + 1; n < info->symtab_size; n++)
	    {
	      addr = bfd_asymbol_value (info->symtab[n]);
	      if (addr > pc
		  && (info->section == NULL
		      || info->section == info->symtab[n]->section))
		{
		      if (addr - pc < size) {
			      size = addr - pc;
		      }
		      break;
		}
	    }
	  /* If the next symbol is after three bytes, we need to
	     print only part of the data, so that we can use either
	     .byte or .short.  */
	    if (size == 3) {
		    size = (pc & 1) ? 1 : 2;
	    }
	}
    }

    if (force_thumb) {
	    is_thumb = TRUE;
    }

    if (is_data) {
	    info->display_endian = little ? BFD_ENDIAN_LITTLE : BFD_ENDIAN_BIG;
    } else {
	    info->display_endian = little_code ? BFD_ENDIAN_LITTLE : BFD_ENDIAN_BIG;
    }

    info->bytes_per_line = 4;

    /* PR 10263: Disassemble data if requested to do so by the user.  */
    if (is_data && ((info->flags & DISASSEMBLE_DATA) == 0)) {
	    int i;

	    /* Size was already set above.  */
	    info->bytes_per_chunk = size;
	    printer = print_insn_data;

	    status = info->read_memory_func (pc, (bfd_byte *)b, size, info);
	    given = 0;
	    if (little) {
		    for (i = size - 1; i >= 0; i--) {
			    given = b[i] | (given << 8);
		    }
	    } else {
		    for (i = 0; i < (int)size; i++) {
			    given = b[i] | (given << 8);
		    }
	    }
    }
  else if (!is_thumb)
    {
      /* In ARM mode endianness is a straightforward issue: the instruction
	 is four bytes long and is either ordered 0123 or 3210.  */
      printer = print_insn_arm;
      info->bytes_per_chunk = 4;
      size = 4;

      status = info->read_memory_func (pc, (bfd_byte *) b, 4, info);
#define N(x) (((unsigned long long )(b[x])) & 0xff)
      if (little_code) {
	      given = N(0) | N(1) <<8 | N(2) << 16 | N(3) << 24;
      } else {
	      given = N(3) | N(2) <<8 | N(1) << 16 | N(0) << 24;
      }
    }
  else
    {
      /* In Thumb mode we have the additional wrinkle of two
	 instruction lengths.  Fortunately, the bits that determine
	 the length of the current instruction are always to be found
	 in the first two bytes.  */
      printer = print_insn_thumb16;
      info->bytes_per_chunk = 2;
      size = 2;

      status = info->read_memory_func (pc, (bfd_byte *) b, 2, info);
      if (little_code) {
	      given = (b[0]) | (b[1] << 8);
      } else {
	      given = (b[1]) | (b[0] << 8);
      }

      if (!status)
	{
	  /* These bit patterns signal a four-byte Thumb
	     instruction.  */
	  if ((given & 0xF800) == 0xF800
	      || (given & 0xF800) == 0xF000
	      || (given & 0xF800) == 0xE800)
	    {
	      status = info->read_memory_func (pc + 2, (bfd_byte *) b, 2, info);
	      if (little_code) {
		      given = (b[0]) | (b[1] << 8) | (given << 16);
	      } else {
		      given = (b[1]) | (b[0] << 8) | (given << 16);
	      }

	      printer = print_insn_thumb32;
	      size = 4;
	    }
	}

	if (ifthen_address != pc) {
		find_ifthen_state (pc, info, little_code);
	}

	if (ifthen_state) {
		if ((ifthen_state & 0xf) == 0x8) {
			ifthen_next_state = 0;
		} else {
			ifthen_next_state = (ifthen_state & 0xe0) | ((ifthen_state & 0xf) << 1);
		}
	}
    }

  if (status)
    {
      info->memory_error_func (status, pc, info);
      return -1;
    }
    if (info->flags & INSN_HAS_RELOC) {
	    /* If the instruction has a reloc associated with it, then
       the offset field in the instruction will actually be the
       addend for the reloc.  (We are using REL type relocs).
       In such cases, we can ignore the pc when computing
       addresses, since the addend is not currently pc-relative.  */
	    pc = 0;
    }

    printer (pc, info, given);

    if (is_thumb) {
	    ifthen_state = ifthen_next_state;
	    ifthen_address += size;
    }
  return size;
}