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
 int /*<<< orphan*/  Field_m_Slot_inst_get (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  Field_n_Slot_inst_get (int /*<<< orphan*/  const) ; 
 int Field_op0_Slot_inst_get (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  Field_op1_Slot_inst_get (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  Field_op2_Slot_inst_get (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  Field_r3_Slot_inst_get (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  Field_r_Slot_inst_get (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  Field_rhi_Slot_inst_get (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  Field_s_Slot_inst_get (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  Field_sr_Slot_inst_get (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  Field_st_Slot_inst_get (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  Field_t3_Slot_inst_get (int /*<<< orphan*/  const) ; 
 int Field_t_Slot_inst_get (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  Field_thi3_Slot_inst_get (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  Field_tlo_Slot_inst_get (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  Field_w_Slot_inst_get (int /*<<< orphan*/  const) ; 

__attribute__((used)) static int
Slot_inst_decode (const xtensa_insnbuf insn)
{
  switch (Field_op0_Slot_inst_get (insn))
    {
    case 0:
      switch (Field_op1_Slot_inst_get (insn))
	{
	case 0:
	  switch (Field_op2_Slot_inst_get (insn))
	    {
	    case 0:
	      switch (Field_r_Slot_inst_get (insn))
		{
		case 0:
		  switch (Field_m_Slot_inst_get (insn))
		    {
		    case 0:
			    if (Field_s_Slot_inst_get (insn) == 0 &&
				    Field_n_Slot_inst_get (insn) == 0) {
				    return 79; /* ill */
			    }
			    break;
		    case 2:
		      switch (Field_n_Slot_inst_get (insn))
			{
			case 0:
			  return 98; /* ret */
			case 1:
			  return 14; /* retw */
			case 2:
			  return 81; /* jx */
			}
		      break;
		    case 3:
		      switch (Field_n_Slot_inst_get (insn))
			{
			case 0:
			  return 77; /* callx0 */
			case 1:
			  return 10; /* callx4 */
			case 2:
			  return 9; /* callx8 */
			case 3:
			  return 8; /* callx12 */
			}
		      break;
		    }
		  break;
		case 1:
		  return 12; /* movsp */
		case 2:
		  if (Field_s_Slot_inst_get (insn) == 0)
		    {
		      switch (Field_t_Slot_inst_get (insn))
			{
			case 0:
			  return 116; /* isync */
			case 1:
			  return 117; /* rsync */
			case 2:
			  return 118; /* esync */
			case 3:
			  return 119; /* dsync */
			case 8:
			  return 0; /* excw */
			case 12:
			  return 114; /* memw */
			case 13:
			  return 115; /* extw */
			case 15:
			  return 97; /* nop */
			}
		    }
		  break;
		case 3:
		  switch (Field_t_Slot_inst_get (insn))
		    {
		    case 0:
		      switch (Field_s_Slot_inst_get (insn))
			{
			case 0:
			  return 1; /* rfe */
			case 2:
			  return 2; /* rfde */
			case 4:
			  return 16; /* rfwo */
			case 5:
			  return 17; /* rfwu */
			}
		      break;
		    case 1:
		      return 316; /* rfi */
		    }
		  break;
		case 4:
		  return 324; /* break */
		case 5:
		  switch (Field_s_Slot_inst_get (insn))
		    {
		    case 0:
			    if (Field_t_Slot_inst_get (insn) == 0) {
				    return 3; /* syscall */
			    }
			    break;
		    case 1:
			    if (Field_t_Slot_inst_get (insn) == 0) {
				    return 4; /* simcall */
			    }
			    break;
		    }
		  break;
		case 6:
		  return 120; /* rsil */
		case 7:
			if (Field_t_Slot_inst_get (insn) == 0) {
				return 317; /* waiti */
			}
			break;
		case 8:
		  return 367; /* any4 */
		case 9:
		  return 368; /* all4 */
		case 10:
		  return 369; /* any8 */
		case 11:
		  return 370; /* all8 */
		}
	      break;
	    case 1:
	      return 49; /* and */
	    case 2:
	      return 50; /* or */
	    case 3:
	      return 51; /* xor */
	    case 4:
	      switch (Field_r_Slot_inst_get (insn))
		{
		case 0:
			if (Field_t_Slot_inst_get (insn) == 0) {
				return 102; /* ssr */
			}
			break;
		case 1:
			if (Field_t_Slot_inst_get (insn) == 0) {
				return 103; /* ssl */
			}
			break;
		case 2:
			if (Field_t_Slot_inst_get (insn) == 0) {
				return 104; /* ssa8l */
			}
			break;
		case 3:
			if (Field_t_Slot_inst_get (insn) == 0) {
				return 105; /* ssa8b */
			}
			break;
		case 4:
			if (Field_thi3_Slot_inst_get (insn) == 0) {
				return 106; /* ssai */
			}
			break;
		case 8:
			if (Field_s_Slot_inst_get (insn) == 0) {
				return 13; /* rotw */
			}
			break;
		case 14:
		  return 448; /* nsa */
		case 15:
		  return 449; /* nsau */
		}
	      break;
	    case 5:
	      switch (Field_r_Slot_inst_get (insn))
		{
		case 1:
		  return 438; /* hwwitlba */
		case 3:
		  return 434; /* ritlb0 */
		case 4:
			if (Field_t_Slot_inst_get (insn) == 0) {
				return 432; /* iitlb */
			}
			break;
		case 5:
		  return 433; /* pitlb */
		case 6:
		  return 436; /* witlb */
		case 7:
		  return 435; /* ritlb1 */
		case 9:
		  return 439; /* hwwdtlba */
		case 11:
		  return 429; /* rdtlb0 */
		case 12:
			if (Field_t_Slot_inst_get (insn) == 0) {
				return 427; /* idtlb */
			}
			break;
		case 13:
		  return 428; /* pdtlb */
		case 14:
		  return 431; /* wdtlb */
		case 15:
		  return 430; /* rdtlb1 */
		}
	      break;
	    case 6:
	      switch (Field_s_Slot_inst_get (insn))
		{
		case 0:
		  return 95; /* neg */
		case 1:
		  return 96; /* abs */
		}
	      break;
	    case 8:
	      return 41; /* add */
	    case 9:
	      return 43; /* addx2 */
	    case 10:
	      return 44; /* addx4 */
	    case 11:
	      return 45; /* addx8 */
	    case 12:
	      return 42; /* sub */
	    case 13:
	      return 46; /* subx2 */
	    case 14:
	      return 47; /* subx4 */
	    case 15:
	      return 48; /* subx8 */
	    }
	  break;
	case 1:
	  switch (Field_op2_Slot_inst_get (insn))
	    {
	    case 0:
	    case 1:
	      return 111; /* slli */
	    case 2:
	    case 3:
	      return 112; /* srai */
	    case 4:
	      return 113; /* srli */
	    case 6:
	      switch (Field_sr_Slot_inst_get (insn))
		{
		case 0:
		  return 129; /* xsr.lbeg */
		case 1:
		  return 123; /* xsr.lend */
		case 2:
		  return 126; /* xsr.lcount */
		case 3:
		  return 132; /* xsr.sar */
		case 4:
		  return 377; /* xsr.br */
		case 5:
		  return 135; /* xsr.litbase */
		case 12:
		  return 456; /* xsr.scompare1 */
		case 16:
		  return 312; /* xsr.acclo */
		case 17:
		  return 315; /* xsr.acchi */
		case 32:
		  return 300; /* xsr.m0 */
		case 33:
		  return 303; /* xsr.m1 */
		case 34:
		  return 306; /* xsr.m2 */
		case 35:
		  return 309; /* xsr.m3 */
		case 72:
		  return 22; /* xsr.windowbase */
		case 73:
		  return 25; /* xsr.windowstart */
		case 83:
		  return 417; /* xsr.ptevaddr */
		case 90:
		  return 420; /* xsr.rasid */
		case 91:
		  return 423; /* xsr.itlbcfg */
		case 92:
		  return 426; /* xsr.dtlbcfg */
		case 96:
		  return 346; /* xsr.ibreakenable */
		case 104:
		  return 358; /* xsr.ddr */
		case 128:
		  return 340; /* xsr.ibreaka0 */
		case 129:
		  return 343; /* xsr.ibreaka1 */
		case 144:
		  return 328; /* xsr.dbreaka0 */
		case 145:
		  return 334; /* xsr.dbreaka1 */
		case 160:
		  return 331; /* xsr.dbreakc0 */
		case 161:
		  return 337; /* xsr.dbreakc1 */
		case 177:
		  return 143; /* xsr.epc1 */
		case 178:
		  return 149; /* xsr.epc2 */
		case 179:
		  return 155; /* xsr.epc3 */
		case 180:
		  return 161; /* xsr.epc4 */
		case 181:
		  return 167; /* xsr.epc5 */
		case 182:
		  return 173; /* xsr.epc6 */
		case 183:
		  return 179; /* xsr.epc7 */
		case 192:
		  return 206; /* xsr.depc */
		case 194:
		  return 185; /* xsr.eps2 */
		case 195:
		  return 188; /* xsr.eps3 */
		case 196:
		  return 191; /* xsr.eps4 */
		case 197:
		  return 194; /* xsr.eps5 */
		case 198:
		  return 197; /* xsr.eps6 */
		case 199:
		  return 200; /* xsr.eps7 */
		case 209:
		  return 146; /* xsr.excsave1 */
		case 210:
		  return 152; /* xsr.excsave2 */
		case 211:
		  return 158; /* xsr.excsave3 */
		case 212:
		  return 164; /* xsr.excsave4 */
		case 213:
		  return 170; /* xsr.excsave5 */
		case 214:
		  return 176; /* xsr.excsave6 */
		case 215:
		  return 182; /* xsr.excsave7 */
		case 224:
		  return 442; /* xsr.cpenable */
		case 228:
		  return 323; /* xsr.intenable */
		case 230:
		  return 140; /* xsr.ps */
		case 231:
		  return 225; /* xsr.vecbase */
		case 232:
		  return 209; /* xsr.exccause */
		case 233:
		  return 349; /* xsr.debugcause */
		case 234:
		  return 380; /* xsr.ccount */
		case 236:
		  return 352; /* xsr.icount */
		case 237:
		  return 355; /* xsr.icountlevel */
		case 238:
		  return 203; /* xsr.excvaddr */
		case 240:
		  return 383; /* xsr.ccompare0 */
		case 241:
		  return 386; /* xsr.ccompare1 */
		case 242:
		  return 389; /* xsr.ccompare2 */
		case 244:
		  return 212; /* xsr.misc0 */
		case 245:
		  return 215; /* xsr.misc1 */
		case 246:
		  return 218; /* xsr.misc2 */
		case 247:
		  return 221; /* xsr.misc3 */
		}
	      break;
	    case 8:
	      return 108; /* src */
	    case 9:
		    if (Field_s_Slot_inst_get (insn) == 0) {
			    return 109; /* srl */
		    }
		    break;
	    case 10:
		    if (Field_t_Slot_inst_get (insn) == 0) {
			    return 107; /* sll */
		    }
		    break;
	    case 11:
		    if (Field_s_Slot_inst_get (insn) == 0) {
			    return 110; /* sra */
		    }
		    break;
	    case 12:
	      return 296; /* mul16u */
	    case 13:
	      return 297; /* mul16s */
	    case 15:
	      switch (Field_r_Slot_inst_get (insn))
		{
		case 0:
		  return 396; /* lict */
		case 1:
		  return 398; /* sict */
		case 2:
		  return 397; /* licw */
		case 3:
		  return 399; /* sicw */
		case 8:
		  return 414; /* ldct */
		case 9:
		  return 413; /* sdct */
		case 14:
			if (Field_t_Slot_inst_get (insn) == 0) {
				return 359; /* rfdo */
			}
			if (Field_t_Slot_inst_get (insn) == 1) {
				return 360; /* rfdd */
			}
			break;
		case 15:
		  return 437; /* ldpte */
		}
	      break;
	    }
	  break;
	case 2:
	  switch (Field_op2_Slot_inst_get (insn))
	    {
	    case 0:
	      return 362; /* andb */
	    case 1:
	      return 363; /* andbc */
	    case 2:
	      return 364; /* orb */
	    case 3:
	      return 365; /* orbc */
	    case 4:
	      return 366; /* xorb */
	    case 8:
	      return 461; /* mull */
	    case 10:
	      return 462; /* muluh */
	    case 11:
	      return 463; /* mulsh */
	    case 12:
	      return 457; /* quou */
	    case 13:
	      return 458; /* quos */
	    case 14:
	      return 459; /* remu */
	    case 15:
	      return 460; /* rems */
	    }
	  break;
	case 3:
	  switch (Field_op2_Slot_inst_get (insn))
	    {
	    case 0:
	      switch (Field_sr_Slot_inst_get (insn))
		{
		case 0:
		  return 127; /* rsr.lbeg */
		case 1:
		  return 121; /* rsr.lend */
		case 2:
		  return 124; /* rsr.lcount */
		case 3:
		  return 130; /* rsr.sar */
		case 4:
		  return 375; /* rsr.br */
		case 5:
		  return 133; /* rsr.litbase */
		case 12:
		  return 454; /* rsr.scompare1 */
		case 16:
		  return 310; /* rsr.acclo */
		case 17:
		  return 313; /* rsr.acchi */
		case 32:
		  return 298; /* rsr.m0 */
		case 33:
		  return 301; /* rsr.m1 */
		case 34:
		  return 304; /* rsr.m2 */
		case 35:
		  return 307; /* rsr.m3 */
		case 72:
		  return 20; /* rsr.windowbase */
		case 73:
		  return 23; /* rsr.windowstart */
		case 83:
		  return 416; /* rsr.ptevaddr */
		case 90:
		  return 418; /* rsr.rasid */
		case 91:
		  return 421; /* rsr.itlbcfg */
		case 92:
		  return 424; /* rsr.dtlbcfg */
		case 96:
		  return 344; /* rsr.ibreakenable */
		case 104:
		  return 356; /* rsr.ddr */
		case 128:
		  return 338; /* rsr.ibreaka0 */
		case 129:
		  return 341; /* rsr.ibreaka1 */
		case 144:
		  return 326; /* rsr.dbreaka0 */
		case 145:
		  return 332; /* rsr.dbreaka1 */
		case 160:
		  return 329; /* rsr.dbreakc0 */
		case 161:
		  return 335; /* rsr.dbreakc1 */
		case 176:
		  return 136; /* rsr.176 */
		case 177:
		  return 141; /* rsr.epc1 */
		case 178:
		  return 147; /* rsr.epc2 */
		case 179:
		  return 153; /* rsr.epc3 */
		case 180:
		  return 159; /* rsr.epc4 */
		case 181:
		  return 165; /* rsr.epc5 */
		case 182:
		  return 171; /* rsr.epc6 */
		case 183:
		  return 177; /* rsr.epc7 */
		case 192:
		  return 204; /* rsr.depc */
		case 194:
		  return 183; /* rsr.eps2 */
		case 195:
		  return 186; /* rsr.eps3 */
		case 196:
		  return 189; /* rsr.eps4 */
		case 197:
		  return 192; /* rsr.eps5 */
		case 198:
		  return 195; /* rsr.eps6 */
		case 199:
		  return 198; /* rsr.eps7 */
		case 208:
		  return 137; /* rsr.208 */
		case 209:
		  return 144; /* rsr.excsave1 */
		case 210:
		  return 150; /* rsr.excsave2 */
		case 211:
		  return 156; /* rsr.excsave3 */
		case 212:
		  return 162; /* rsr.excsave4 */
		case 213:
		  return 168; /* rsr.excsave5 */
		case 214:
		  return 174; /* rsr.excsave6 */
		case 215:
		  return 180; /* rsr.excsave7 */
		case 224:
		  return 440; /* rsr.cpenable */
		case 226:
		  return 318; /* rsr.interrupt */
		case 228:
		  return 321; /* rsr.intenable */
		case 230:
		  return 138; /* rsr.ps */
		case 231:
		  return 223; /* rsr.vecbase */
		case 232:
		  return 207; /* rsr.exccause */
		case 233:
		  return 347; /* rsr.debugcause */
		case 234:
		  return 378; /* rsr.ccount */
		case 235:
		  return 222; /* rsr.prid */
		case 236:
		  return 350; /* rsr.icount */
		case 237:
		  return 353; /* rsr.icountlevel */
		case 238:
		  return 201; /* rsr.excvaddr */
		case 240:
		  return 381; /* rsr.ccompare0 */
		case 241:
		  return 384; /* rsr.ccompare1 */
		case 242:
		  return 387; /* rsr.ccompare2 */
		case 244:
		  return 210; /* rsr.misc0 */
		case 245:
		  return 213; /* rsr.misc1 */
		case 246:
		  return 216; /* rsr.misc2 */
		case 247:
		  return 219; /* rsr.misc3 */
		}
	      break;
	    case 1:
	      switch (Field_sr_Slot_inst_get (insn))
		{
		case 0:
		  return 128; /* wsr.lbeg */
		case 1:
		  return 122; /* wsr.lend */
		case 2:
		  return 125; /* wsr.lcount */
		case 3:
		  return 131; /* wsr.sar */
		case 4:
		  return 376; /* wsr.br */
		case 5:
		  return 134; /* wsr.litbase */
		case 12:
		  return 455; /* wsr.scompare1 */
		case 16:
		  return 311; /* wsr.acclo */
		case 17:
		  return 314; /* wsr.acchi */
		case 32:
		  return 299; /* wsr.m0 */
		case 33:
		  return 302; /* wsr.m1 */
		case 34:
		  return 305; /* wsr.m2 */
		case 35:
		  return 308; /* wsr.m3 */
		case 72:
		  return 21; /* wsr.windowbase */
		case 73:
		  return 24; /* wsr.windowstart */
		case 83:
		  return 415; /* wsr.ptevaddr */
		case 89:
		  return 361; /* wsr.mmid */
		case 90:
		  return 419; /* wsr.rasid */
		case 91:
		  return 422; /* wsr.itlbcfg */
		case 92:
		  return 425; /* wsr.dtlbcfg */
		case 96:
		  return 345; /* wsr.ibreakenable */
		case 104:
		  return 357; /* wsr.ddr */
		case 128:
		  return 339; /* wsr.ibreaka0 */
		case 129:
		  return 342; /* wsr.ibreaka1 */
		case 144:
		  return 327; /* wsr.dbreaka0 */
		case 145:
		  return 333; /* wsr.dbreaka1 */
		case 160:
		  return 330; /* wsr.dbreakc0 */
		case 161:
		  return 336; /* wsr.dbreakc1 */
		case 177:
		  return 142; /* wsr.epc1 */
		case 178:
		  return 148; /* wsr.epc2 */
		case 179:
		  return 154; /* wsr.epc3 */
		case 180:
		  return 160; /* wsr.epc4 */
		case 181:
		  return 166; /* wsr.epc5 */
		case 182:
		  return 172; /* wsr.epc6 */
		case 183:
		  return 178; /* wsr.epc7 */
		case 192:
		  return 205; /* wsr.depc */
		case 194:
		  return 184; /* wsr.eps2 */
		case 195:
		  return 187; /* wsr.eps3 */
		case 196:
		  return 190; /* wsr.eps4 */
		case 197:
		  return 193; /* wsr.eps5 */
		case 198:
		  return 196; /* wsr.eps6 */
		case 199:
		  return 199; /* wsr.eps7 */
		case 209:
		  return 145; /* wsr.excsave1 */
		case 210:
		  return 151; /* wsr.excsave2 */
		case 211:
		  return 157; /* wsr.excsave3 */
		case 212:
		  return 163; /* wsr.excsave4 */
		case 213:
		  return 169; /* wsr.excsave5 */
		case 214:
		  return 175; /* wsr.excsave6 */
		case 215:
		  return 181; /* wsr.excsave7 */
		case 224:
		  return 441; /* wsr.cpenable */
		case 226:
		  return 319; /* wsr.intset */
		case 227:
		  return 320; /* wsr.intclear */
		case 228:
		  return 322; /* wsr.intenable */
		case 230:
		  return 139; /* wsr.ps */
		case 231:
		  return 224; /* wsr.vecbase */
		case 232:
		  return 208; /* wsr.exccause */
		case 233:
		  return 348; /* wsr.debugcause */
		case 234:
		  return 379; /* wsr.ccount */
		case 236:
		  return 351; /* wsr.icount */
		case 237:
		  return 354; /* wsr.icountlevel */
		case 238:
		  return 202; /* wsr.excvaddr */
		case 240:
		  return 382; /* wsr.ccompare0 */
		case 241:
		  return 385; /* wsr.ccompare1 */
		case 242:
		  return 388; /* wsr.ccompare2 */
		case 244:
		  return 211; /* wsr.misc0 */
		case 245:
		  return 214; /* wsr.misc1 */
		case 246:
		  return 217; /* wsr.misc2 */
		case 247:
		  return 220; /* wsr.misc3 */
		}
	      break;
	    case 2:
	      return 450; /* sext */
	    case 3:
	      return 443; /* clamps */
	    case 4:
	      return 444; /* min */
	    case 5:
	      return 445; /* max */
	    case 6:
	      return 446; /* minu */
	    case 7:
	      return 447; /* maxu */
	    case 8:
	      return 91; /* moveqz */
	    case 9:
	      return 92; /* movnez */
	    case 10:
	      return 93; /* movltz */
	    case 11:
	      return 94; /* movgez */
	    case 12:
	      return 373; /* movf */
	    case 13:
	      return 374; /* movt */
	    case 14:
	      switch (Field_st_Slot_inst_get (insn))
		{
		case 231:
		  return 37; /* rur.threadptr */
		case 232:
		  return 464; /* rur.fcr */
		case 233:
		  return 466; /* rur.fsr */
		}
	      break;
	    case 15:
	      switch (Field_sr_Slot_inst_get (insn))
		{
		case 231:
		  return 38; /* wur.threadptr */
		case 232:
		  return 465; /* wur.fcr */
		case 233:
		  return 467; /* wur.fsr */
		}
	      break;
	    }
	  break;
	case 4:
	case 5:
	  return 78; /* extui */
	case 8:
	  switch (Field_op2_Slot_inst_get (insn))
	    {
	    case 0:
	      return 500; /* lsx */
	    case 1:
	      return 501; /* lsxu */
	    case 4:
	      return 504; /* ssx */
	    case 5:
	      return 505; /* ssxu */
	    }
	  break;
	case 9:
	  switch (Field_op2_Slot_inst_get (insn))
	    {
	    case 0:
	      return 18; /* l32e */
	    case 4:
	      return 19; /* s32e */
	    }
	  break;
	case 10:
	  switch (Field_op2_Slot_inst_get (insn))
	    {
	    case 0:
	      return 468; /* add.s */
	    case 1:
	      return 469; /* sub.s */
	    case 2:
	      return 470; /* mul.s */
	    case 4:
	      return 471; /* madd.s */
	    case 5:
	      return 472; /* msub.s */
	    case 8:
	      return 491; /* round.s */
	    case 9:
	      return 494; /* trunc.s */
	    case 10:
	      return 493; /* floor.s */
	    case 11:
	      return 492; /* ceil.s */
	    case 12:
	      return 489; /* float.s */
	    case 13:
	      return 490; /* ufloat.s */
	    case 14:
	      return 495; /* utrunc.s */
	    case 15:
	      switch (Field_t_Slot_inst_get (insn))
		{
		case 0:
		  return 480; /* mov.s */
		case 1:
		  return 479; /* abs.s */
		case 4:
		  return 496; /* rfr */
		case 5:
		  return 497; /* wfr */
		case 6:
		  return 481; /* neg.s */
		}
	      break;
	    }
	  break;
	case 11:
	  switch (Field_op2_Slot_inst_get (insn))
	    {
	    case 1:
	      return 482; /* un.s */
	    case 2:
	      return 483; /* oeq.s */
	    case 3:
	      return 484; /* ueq.s */
	    case 4:
	      return 485; /* olt.s */
	    case 5:
	      return 486; /* ult.s */
	    case 6:
	      return 487; /* ole.s */
	    case 7:
	      return 488; /* ule.s */
	    case 8:
	      return 475; /* moveqz.s */
	    case 9:
	      return 476; /* movnez.s */
	    case 10:
	      return 477; /* movltz.s */
	    case 11:
	      return 478; /* movgez.s */
	    case 12:
	      return 473; /* movf.s */
	    case 13:
	      return 474; /* movt.s */
	    }
	  break;
	}
      break;
    case 1:
      return 85; /* l32r */
    case 2:
      switch (Field_r_Slot_inst_get (insn))
	{
	case 0:
	  return 86; /* l8ui */
	case 1:
	  return 82; /* l16ui */
	case 2:
	  return 84; /* l32i */
	case 4:
	  return 101; /* s8i */
	case 5:
	  return 99; /* s16i */
	case 6:
	  return 100; /* s32i */
	case 7:
	  switch (Field_t_Slot_inst_get (insn))
	    {
	    case 0:
	      return 406; /* dpfr */
	    case 1:
	      return 407; /* dpfw */
	    case 2:
	      return 408; /* dpfro */
	    case 3:
	      return 409; /* dpfwo */
	    case 4:
	      return 400; /* dhwb */
	    case 5:
	      return 401; /* dhwbi */
	    case 6:
	      return 404; /* dhi */
	    case 7:
	      return 405; /* dii */
	    case 8:
	      switch (Field_op1_Slot_inst_get (insn))
		{
		case 0:
		  return 410; /* dpfl */
		case 2:
		  return 411; /* dhu */
		case 3:
		  return 412; /* diu */
		case 4:
		  return 402; /* diwb */
		case 5:
		  return 403; /* diwbi */
		}
	      break;
	    case 12:
	      return 390; /* ipf */
	    case 13:
	      switch (Field_op1_Slot_inst_get (insn))
		{
		case 0:
		  return 392; /* ipfl */
		case 2:
		  return 393; /* ihu */
		case 3:
		  return 394; /* iiu */
		}
	      break;
	    case 14:
	      return 391; /* ihi */
	    case 15:
	      return 395; /* iii */
	    }
	  break;
	case 9:
	  return 83; /* l16si */
	case 10:
	  return 90; /* movi */
	case 11:
	  return 451; /* l32ai */
	case 12:
	  return 39; /* addi */
	case 13:
	  return 40; /* addmi */
	case 14:
	  return 453; /* s32c1i */
	case 15:
	  return 452; /* s32ri */
	}
      break;
    case 3:
      switch (Field_r_Slot_inst_get (insn))
	{
	case 0:
	  return 498; /* lsi */
	case 4:
	  return 502; /* ssi */
	case 8:
	  return 499; /* lsiu */
	case 12:
	  return 503; /* ssiu */
	}
      break;
    case 4:
      switch (Field_op2_Slot_inst_get (insn))
	{
	case 0:
	  switch (Field_op1_Slot_inst_get (insn))
	    {
	    case 8:
		    if (Field_t3_Slot_inst_get (insn) == 0 &&
			    Field_tlo_Slot_inst_get (insn) == 0 &&
			    Field_r3_Slot_inst_get (insn) == 0) {
			    return 287; /* mula.dd.ll.ldinc */
		    }
		    break;
	    case 9:
		    if (Field_t3_Slot_inst_get (insn) == 0 &&
			    Field_tlo_Slot_inst_get (insn) == 0 &&
			    Field_r3_Slot_inst_get (insn) == 0) {
			    return 289; /* mula.dd.hl.ldinc */
		    }
		    break;
	    case 10:
		    if (Field_t3_Slot_inst_get (insn) == 0 &&
			    Field_tlo_Slot_inst_get (insn) == 0 &&
			    Field_r3_Slot_inst_get (insn) == 0) {
			    return 291; /* mula.dd.lh.ldinc */
		    }
		    break;
	    case 11:
		    if (Field_t3_Slot_inst_get (insn) == 0 &&
			    Field_tlo_Slot_inst_get (insn) == 0 &&
			    Field_r3_Slot_inst_get (insn) == 0) {
			    return 293; /* mula.dd.hh.ldinc */
		    }
		    break;
	    }
	  break;
	case 1:
	  switch (Field_op1_Slot_inst_get (insn))
	    {
	    case 8:
		    if (Field_t3_Slot_inst_get (insn) == 0 &&
			    Field_tlo_Slot_inst_get (insn) == 0 &&
			    Field_r3_Slot_inst_get (insn) == 0) {
			    return 286; /* mula.dd.ll.lddec */
		    }
		    break;
	    case 9:
		    if (Field_t3_Slot_inst_get (insn) == 0 &&
			    Field_tlo_Slot_inst_get (insn) == 0 &&
			    Field_r3_Slot_inst_get (insn) == 0) {
			    return 288; /* mula.dd.hl.lddec */
		    }
		    break;
	    case 10:
		    if (Field_t3_Slot_inst_get (insn) == 0 &&
			    Field_tlo_Slot_inst_get (insn) == 0 &&
			    Field_r3_Slot_inst_get (insn) == 0) {
			    return 290; /* mula.dd.lh.lddec */
		    }
		    break;
	    case 11:
		    if (Field_t3_Slot_inst_get (insn) == 0 &&
			    Field_tlo_Slot_inst_get (insn) == 0 &&
			    Field_r3_Slot_inst_get (insn) == 0) {
			    return 292; /* mula.dd.hh.lddec */
		    }
		    break;
	    }
	  break;
	case 2:
	  switch (Field_op1_Slot_inst_get (insn))
	    {
	    case 4:
		    if (Field_s_Slot_inst_get (insn) == 0 &&
			    Field_w_Slot_inst_get (insn) == 0 &&
			    Field_r3_Slot_inst_get (insn) == 0 &&
			    Field_t3_Slot_inst_get (insn) == 0 &&
			    Field_tlo_Slot_inst_get (insn) == 0) {
			    return 242; /* mul.dd.ll */
		    }
		    break;
	    case 5:
		    if (Field_s_Slot_inst_get (insn) == 0 &&
			    Field_w_Slot_inst_get (insn) == 0 &&
			    Field_r3_Slot_inst_get (insn) == 0 &&
			    Field_t3_Slot_inst_get (insn) == 0 &&
			    Field_tlo_Slot_inst_get (insn) == 0) {
			    return 243; /* mul.dd.hl */
		    }
		    break;
	    case 6:
		    if (Field_s_Slot_inst_get (insn) == 0 &&
			    Field_w_Slot_inst_get (insn) == 0 &&
			    Field_r3_Slot_inst_get (insn) == 0 &&
			    Field_t3_Slot_inst_get (insn) == 0 &&
			    Field_tlo_Slot_inst_get (insn) == 0) {
			    return 244; /* mul.dd.lh */
		    }
		    break;
	    case 7:
		    if (Field_s_Slot_inst_get (insn) == 0 &&
			    Field_w_Slot_inst_get (insn) == 0 &&
			    Field_r3_Slot_inst_get (insn) == 0 &&
			    Field_t3_Slot_inst_get (insn) == 0 &&
			    Field_tlo_Slot_inst_get (insn) == 0) {
			    return 245; /* mul.dd.hh */
		    }
		    break;
	    case 8:
		    if (Field_s_Slot_inst_get (insn) == 0 &&
			    Field_w_Slot_inst_get (insn) == 0 &&
			    Field_r3_Slot_inst_get (insn) == 0 &&
			    Field_t3_Slot_inst_get (insn) == 0 &&
			    Field_tlo_Slot_inst_get (insn) == 0) {
			    return 270; /* mula.dd.ll */
		    }
		    break;
	    case 9:
		    if (Field_s_Slot_inst_get (insn) == 0 &&
			    Field_w_Slot_inst_get (insn) == 0 &&
			    Field_r3_Slot_inst_get (insn) == 0 &&
			    Field_t3_Slot_inst_get (insn) == 0 &&
			    Field_tlo_Slot_inst_get (insn) == 0) {
			    return 271; /* mula.dd.hl */
		    }
		    break;
	    case 10:
		    if (Field_s_Slot_inst_get (insn) == 0 &&
			    Field_w_Slot_inst_get (insn) == 0 &&
			    Field_r3_Slot_inst_get (insn) == 0 &&
			    Field_t3_Slot_inst_get (insn) == 0 &&
			    Field_tlo_Slot_inst_get (insn) == 0) {
			    return 272; /* mula.dd.lh */
		    }
		    break;
	    case 11:
		    if (Field_s_Slot_inst_get (insn) == 0 &&
			    Field_w_Slot_inst_get (insn) == 0 &&
			    Field_r3_Slot_inst_get (insn) == 0 &&
			    Field_t3_Slot_inst_get (insn) == 0 &&
			    Field_tlo_Slot_inst_get (insn) == 0) {
			    return 273; /* mula.dd.hh */
		    }
		    break;
	    case 12:
		    if (Field_s_Slot_inst_get (insn) == 0 &&
			    Field_w_Slot_inst_get (insn) == 0 &&
			    Field_r3_Slot_inst_get (insn) == 0 &&
			    Field_t3_Slot_inst_get (insn) == 0 &&
			    Field_tlo_Slot_inst_get (insn) == 0) {
			    return 274; /* muls.dd.ll */
		    }
		    break;
	    case 13:
		    if (Field_s_Slot_inst_get (insn) == 0 &&
			    Field_w_Slot_inst_get (insn) == 0 &&
			    Field_r3_Slot_inst_get (insn) == 0 &&
			    Field_t3_Slot_inst_get (insn) == 0 &&
			    Field_tlo_Slot_inst_get (insn) == 0) {
			    return 275; /* muls.dd.hl */
		    }
		    break;
	    case 14:
		    if (Field_s_Slot_inst_get (insn) == 0 &&
			    Field_w_Slot_inst_get (insn) == 0 &&
			    Field_r3_Slot_inst_get (insn) == 0 &&
			    Field_t3_Slot_inst_get (insn) == 0 &&
			    Field_tlo_Slot_inst_get (insn) == 0) {
			    return 276; /* muls.dd.lh */
		    }
		    break;
	    case 15:
		    if (Field_s_Slot_inst_get (insn) == 0 &&
			    Field_w_Slot_inst_get (insn) == 0 &&
			    Field_r3_Slot_inst_get (insn) == 0 &&
			    Field_t3_Slot_inst_get (insn) == 0 &&
			    Field_tlo_Slot_inst_get (insn) == 0) {
			    return 277; /* muls.dd.hh */
		    }
		    break;
	    }
	  break;
	case 3:
	  switch (Field_op1_Slot_inst_get (insn))
	    {
	    case 4:
		    if (Field_r_Slot_inst_get (insn) == 0 &&
			    Field_t3_Slot_inst_get (insn) == 0 &&
			    Field_tlo_Slot_inst_get (insn) == 0) {
			    return 234; /* mul.ad.ll */
		    }
		    break;
	    case 5:
		    if (Field_r_Slot_inst_get (insn) == 0 &&
			    Field_t3_Slot_inst_get (insn) == 0 &&
			    Field_tlo_Slot_inst_get (insn) == 0) {
			    return 235; /* mul.ad.hl */
		    }
		    break;
	    case 6:
		    if (Field_r_Slot_inst_get (insn) == 0 &&
			    Field_t3_Slot_inst_get (insn) == 0 &&
			    Field_tlo_Slot_inst_get (insn) == 0) {
			    return 236; /* mul.ad.lh */
		    }
		    break;
	    case 7:
		    if (Field_r_Slot_inst_get (insn) == 0 &&
			    Field_t3_Slot_inst_get (insn) == 0 &&
			    Field_tlo_Slot_inst_get (insn) == 0) {
			    return 237; /* mul.ad.hh */
		    }
		    break;
	    case 8:
		    if (Field_r_Slot_inst_get (insn) == 0 &&
			    Field_t3_Slot_inst_get (insn) == 0 &&
			    Field_tlo_Slot_inst_get (insn) == 0) {
			    return 254; /* mula.ad.ll */
		    }
		    break;
	    case 9:
		    if (Field_r_Slot_inst_get (insn) == 0 &&
			    Field_t3_Slot_inst_get (insn) == 0 &&
			    Field_tlo_Slot_inst_get (insn) == 0) {
			    return 255; /* mula.ad.hl */
		    }
		    break;
	    case 10:
		    if (Field_r_Slot_inst_get (insn) == 0 &&
			    Field_t3_Slot_inst_get (insn) == 0 &&
			    Field_tlo_Slot_inst_get (insn) == 0) {
			    return 256; /* mula.ad.lh */
		    }
		    break;
	    case 11:
		    if (Field_r_Slot_inst_get (insn) == 0 &&
			    Field_t3_Slot_inst_get (insn) == 0 &&
			    Field_tlo_Slot_inst_get (insn) == 0) {
			    return 257; /* mula.ad.hh */
		    }
		    break;
	    case 12:
		    if (Field_r_Slot_inst_get (insn) == 0 &&
			    Field_t3_Slot_inst_get (insn) == 0 &&
			    Field_tlo_Slot_inst_get (insn) == 0) {
			    return 258; /* muls.ad.ll */
		    }
		    break;
	    case 13:
		    if (Field_r_Slot_inst_get (insn) == 0 &&
			    Field_t3_Slot_inst_get (insn) == 0 &&
			    Field_tlo_Slot_inst_get (insn) == 0) {
			    return 259; /* muls.ad.hl */
		    }
		    break;
	    case 14:
		    if (Field_r_Slot_inst_get (insn) == 0 &&
			    Field_t3_Slot_inst_get (insn) == 0 &&
			    Field_tlo_Slot_inst_get (insn) == 0) {
			    return 260; /* muls.ad.lh */
		    }
		    break;
	    case 15:
		    if (Field_r_Slot_inst_get (insn) == 0 &&
			    Field_t3_Slot_inst_get (insn) == 0 &&
			    Field_tlo_Slot_inst_get (insn) == 0) {
			    return 261; /* muls.ad.hh */
		    }
		    break;
	    }
	  break;
	case 4:
	  switch (Field_op1_Slot_inst_get (insn))
	    {
	    case 8:
		    if (Field_r3_Slot_inst_get (insn) == 0) {
			    return 279; /* mula.da.ll.ldinc */
		    }
		    break;
	    case 9:
		    if (Field_r3_Slot_inst_get (insn) == 0) {
			    return 281; /* mula.da.hl.ldinc */
		    }
		    break;
	    case 10:
		    if (Field_r3_Slot_inst_get (insn) == 0) {
			    return 283; /* mula.da.lh.ldinc */
		    }
		    break;
	    case 11:
		    if (Field_r3_Slot_inst_get (insn) == 0) {
			    return 285; /* mula.da.hh.ldinc */
		    }
		    break;
	    }
	  break;
	case 5:
	  switch (Field_op1_Slot_inst_get (insn))
	    {
	    case 8:
		    if (Field_r3_Slot_inst_get (insn) == 0) {
			    return 278; /* mula.da.ll.lddec */
		    }
		    break;
	    case 9:
		    if (Field_r3_Slot_inst_get (insn) == 0) {
			    return 280; /* mula.da.hl.lddec */
		    }
		    break;
	    case 10:
		    if (Field_r3_Slot_inst_get (insn) == 0) {
			    return 282; /* mula.da.lh.lddec */
		    }
		    break;
	    case 11:
		    if (Field_r3_Slot_inst_get (insn) == 0) {
			    return 284; /* mula.da.hh.lddec */
		    }
		    break;
	    }
	  break;
	case 6:
	  switch (Field_op1_Slot_inst_get (insn))
	    {
	    case 4:
		    if (Field_s_Slot_inst_get (insn) == 0 &&
			    Field_w_Slot_inst_get (insn) == 0 &&
			    Field_r3_Slot_inst_get (insn) == 0) {
			    return 238; /* mul.da.ll */
		    }
		    break;
	    case 5:
		    if (Field_s_Slot_inst_get (insn) == 0 &&
			    Field_w_Slot_inst_get (insn) == 0 &&
			    Field_r3_Slot_inst_get (insn) == 0) {
			    return 239; /* mul.da.hl */
		    }
		    break;
	    case 6:
		    if (Field_s_Slot_inst_get (insn) == 0 &&
			    Field_w_Slot_inst_get (insn) == 0 &&
			    Field_r3_Slot_inst_get (insn) == 0) {
			    return 240; /* mul.da.lh */
		    }
		    break;
	    case 7:
		    if (Field_s_Slot_inst_get (insn) == 0 &&
			    Field_w_Slot_inst_get (insn) == 0 &&
			    Field_r3_Slot_inst_get (insn) == 0) {
			    return 241; /* mul.da.hh */
		    }
		    break;
	    case 8:
		    if (Field_s_Slot_inst_get (insn) == 0 &&
			    Field_w_Slot_inst_get (insn) == 0 &&
			    Field_r3_Slot_inst_get (insn) == 0) {
			    return 262; /* mula.da.ll */
		    }
		    break;
	    case 9:
		    if (Field_s_Slot_inst_get (insn) == 0 &&
			    Field_w_Slot_inst_get (insn) == 0 &&
			    Field_r3_Slot_inst_get (insn) == 0) {
			    return 263; /* mula.da.hl */
		    }
		    break;
	    case 10:
		    if (Field_s_Slot_inst_get (insn) == 0 &&
			    Field_w_Slot_inst_get (insn) == 0 &&
			    Field_r3_Slot_inst_get (insn) == 0) {
			    return 264; /* mula.da.lh */
		    }
		    break;
	    case 11:
		    if (Field_s_Slot_inst_get (insn) == 0 &&
			    Field_w_Slot_inst_get (insn) == 0 &&
			    Field_r3_Slot_inst_get (insn) == 0) {
			    return 265; /* mula.da.hh */
		    }
		    break;
	    case 12:
		    if (Field_s_Slot_inst_get (insn) == 0 &&
			    Field_w_Slot_inst_get (insn) == 0 &&
			    Field_r3_Slot_inst_get (insn) == 0) {
			    return 266; /* muls.da.ll */
		    }
		    break;
	    case 13:
		    if (Field_s_Slot_inst_get (insn) == 0 &&
			    Field_w_Slot_inst_get (insn) == 0 &&
			    Field_r3_Slot_inst_get (insn) == 0) {
			    return 267; /* muls.da.hl */
		    }
		    break;
	    case 14:
		    if (Field_s_Slot_inst_get (insn) == 0 &&
			    Field_w_Slot_inst_get (insn) == 0 &&
			    Field_r3_Slot_inst_get (insn) == 0) {
			    return 268; /* muls.da.lh */
		    }
		    break;
	    case 15:
		    if (Field_s_Slot_inst_get (insn) == 0 &&
			    Field_w_Slot_inst_get (insn) == 0 &&
			    Field_r3_Slot_inst_get (insn) == 0) {
			    return 269; /* muls.da.hh */
		    }
		    break;
	    }
	  break;
	case 7:
	  switch (Field_op1_Slot_inst_get (insn))
	    {
	    case 0:
		    if (Field_r_Slot_inst_get (insn) == 0) {
			    return 230; /* umul.aa.ll */
		    }
		    break;
	    case 1:
		    if (Field_r_Slot_inst_get (insn) == 0) {
			    return 231; /* umul.aa.hl */
		    }
		    break;
	    case 2:
		    if (Field_r_Slot_inst_get (insn) == 0) {
			    return 232; /* umul.aa.lh */
		    }
		    break;
	    case 3:
		    if (Field_r_Slot_inst_get (insn) == 0) {
			    return 233; /* umul.aa.hh */
		    }
		    break;
	    case 4:
		    if (Field_r_Slot_inst_get (insn) == 0) {
			    return 226; /* mul.aa.ll */
		    }
		    break;
	    case 5:
		    if (Field_r_Slot_inst_get (insn) == 0) {
			    return 227; /* mul.aa.hl */
		    }
		    break;
	    case 6:
		    if (Field_r_Slot_inst_get (insn) == 0) {
			    return 228; /* mul.aa.lh */
		    }
		    break;
	    case 7:
		    if (Field_r_Slot_inst_get (insn) == 0) {
			    return 229; /* mul.aa.hh */
		    }
		    break;
	    case 8:
		    if (Field_r_Slot_inst_get (insn) == 0) {
			    return 246; /* mula.aa.ll */
		    }
		    break;
	    case 9:
		    if (Field_r_Slot_inst_get (insn) == 0) {
			    return 247; /* mula.aa.hl */
		    }
		    break;
	    case 10:
		    if (Field_r_Slot_inst_get (insn) == 0) {
			    return 248; /* mula.aa.lh */
		    }
		    break;
	    case 11:
		    if (Field_r_Slot_inst_get (insn) == 0) {
			    return 249; /* mula.aa.hh */
		    }
		    break;
	    case 12:
		    if (Field_r_Slot_inst_get (insn) == 0) {
			    return 250; /* muls.aa.ll */
		    }
		    break;
	    case 13:
		    if (Field_r_Slot_inst_get (insn) == 0) {
			    return 251; /* muls.aa.hl */
		    }
		    break;
	    case 14:
		    if (Field_r_Slot_inst_get (insn) == 0) {
			    return 252; /* muls.aa.lh */
		    }
		    break;
	    case 15:
		    if (Field_r_Slot_inst_get (insn) == 0) {
			    return 253; /* muls.aa.hh */
		    }
		    break;
	    }
	  break;
	case 8:
		if (Field_op1_Slot_inst_get (insn) == 0 &&
			Field_t_Slot_inst_get (insn) == 0 &&
			Field_rhi_Slot_inst_get (insn) == 0) {
			return 295; /* ldinc */
		}
		break;
	case 9:
		if (Field_op1_Slot_inst_get (insn) == 0 &&
			Field_t_Slot_inst_get (insn) == 0 &&
			Field_rhi_Slot_inst_get (insn) == 0) {
			return 294; /* lddec */
		}
		break;
	}
      break;
    case 5:
      switch (Field_n_Slot_inst_get (insn))
	{
	case 0:
	  return 76; /* call0 */
	case 1:
	  return 7; /* call4 */
	case 2:
	  return 6; /* call8 */
	case 3:
	  return 5; /* call12 */
	}
      break;
    case 6:
      switch (Field_n_Slot_inst_get (insn))
	{
	case 0:
	  return 80; /* j */
	case 1:
	  switch (Field_m_Slot_inst_get (insn))
	    {
	    case 0:
	      return 72; /* beqz */
	    case 1:
	      return 73; /* bnez */
	    case 2:
	      return 75; /* bltz */
	    case 3:
	      return 74; /* bgez */
	    }
	  break;
	case 2:
	  switch (Field_m_Slot_inst_get (insn))
	    {
	    case 0:
	      return 52; /* beqi */
	    case 1:
	      return 53; /* bnei */
	    case 2:
	      return 55; /* blti */
	    case 3:
	      return 54; /* bgei */
	    }
	  break;
	case 3:
	  switch (Field_m_Slot_inst_get (insn))
	    {
	    case 0:
	      return 11; /* entry */
	    case 1:
	      switch (Field_r_Slot_inst_get (insn))
		{
		case 0:
		  return 371; /* bf */
		case 1:
		  return 372; /* bt */
		case 8:
		  return 87; /* loop */
		case 9:
		  return 88; /* loopnez */
		case 10:
		  return 89; /* loopgtz */
		}
	      break;
	    case 2:
	      return 59; /* bltui */
	    case 3:
	      return 58; /* bgeui */
	    }
	  break;
	}
      break;
    case 7:
      switch (Field_r_Slot_inst_get (insn))
	{
	case 0:
	  return 67; /* bnone */
	case 1:
	  return 60; /* beq */
	case 2:
	  return 63; /* blt */
	case 3:
	  return 65; /* bltu */
	case 4:
	  return 68; /* ball */
	case 5:
	  return 70; /* bbc */
	case 6:
	case 7:
	  return 56; /* bbci */
	case 8:
	  return 66; /* bany */
	case 9:
	  return 61; /* bne */
	case 10:
	  return 62; /* bge */
	case 11:
	  return 64; /* bgeu */
	case 12:
	  return 69; /* bnall */
	case 13:
	  return 71; /* bbs */
	case 14:
	case 15:
	  return 57; /* bbsi */
	}
      break;
    }
  return 0;
}