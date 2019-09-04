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
typedef  int /*<<< orphan*/  xtensa_insnbuf ;

/* Variables and functions */
 int /*<<< orphan*/  Field_i_Slot_inst16b_get (int /*<<< orphan*/  const) ; 
 int Field_op0_Slot_inst16b_get (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  Field_r_Slot_inst16b_get (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  Field_s_Slot_inst16b_get (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  Field_t_Slot_inst16b_get (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  Field_z_Slot_inst16b_get (int /*<<< orphan*/  const) ; 

__attribute__((used)) static int
Slot_inst16b_decode (const xtensa_insnbuf insn)
{
  switch (Field_op0_Slot_inst16b_get (insn))
    {
    case 12:
      switch (Field_i_Slot_inst16b_get (insn))
	{
	case 0:
	  return 33; /* movi.n */
	case 1:
	  switch (Field_z_Slot_inst16b_get (insn))
	    {
	    case 0:
	      return 28; /* beqz.n */
	    case 1:
	      return 29; /* bnez.n */
	    }
	  break;
	}
      break;
    case 13:
      switch (Field_r_Slot_inst16b_get (insn))
	{
	case 0:
	  return 32; /* mov.n */
	case 15:
	  switch (Field_t_Slot_inst16b_get (insn))
	    {
	    case 0:
	      return 35; /* ret.n */
	    case 1:
	      return 15; /* retw.n */
	    case 2:
	      return 325; /* break.n */
	    case 3:
		    if (Field_s_Slot_inst16b_get (insn) == 0) {
			    return 34; /* nop.n */
		    }
		    break;
	    case 6:
		    if (Field_s_Slot_inst16b_get (insn) == 0) {
			    return 30; /* ill.n */
		    }
		    break;
	    }
	  break;
	}
      break;
    }
  return 0;
}