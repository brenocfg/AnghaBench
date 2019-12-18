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
typedef  int arc_insn ;

/* Variables and functions */

int
ac_get_load_sdasym_insn_type (arc_insn insn, int compact_insn_16)
{
  int load_type = -1;

  /* ld[b/w]_s */
  if (compact_insn_16)
    {
      switch (insn & 0xfe00)
	{
	  /* ld_s */
	case 0xc800:
	  load_type = 10;
	  break;

	  /* ldb_s */
	case 0xca00:
	  load_type = 11;
	  break;

	  /* ldw_s */
	case 0xcc00:
	  load_type = 12;
	  break;
	}
    }
  else
    {
      /* ld/ldw/ldb */
      switch (insn & 0xf8000180)
	{
	  /* ld */
	case 0x10000000:
		if (((insn >> 9) & 3) == 3) {
			load_type = 0;
		} else {
			load_type = 1;
		}
		break;

		/* ldw */
	case 0x10000100:
		if (((insn >> 9) & 3) == 3) {
			load_type = 2;
		} else {
			load_type = 1;
		}
		break;

		/* ldb */
	case 0x10000080:
	  load_type = 1;
	  break;

	}
    }

  return load_type;
}