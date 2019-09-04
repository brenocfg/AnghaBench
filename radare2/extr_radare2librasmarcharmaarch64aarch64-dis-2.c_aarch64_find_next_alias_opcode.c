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
typedef  int /*<<< orphan*/  aarch64_opcode ;

/* Variables and functions */
 int /*<<< orphan*/  const* aarch64_opcode_table ; 

const aarch64_opcode *
aarch64_find_next_alias_opcode (const aarch64_opcode *opcode)
{
  /* Use the index as the key to locate the next opcode.  */
  int key = opcode - aarch64_opcode_table;
  int value;
  switch (key)
    {
    case 3: value = 2; break;	/* ngc --> sbc.  */
    case 5: value = 4; break;	/* ngcs --> sbcs.  */
    case 8: value = 7; break;	/* cmn --> adds.  */
    case 11: value = 10; break;	/* cmp --> subs.  */
    case 13: value = 12; break;	/* mov --> add.  */
    case 15: value = 14; break;	/* cmn --> adds.  */
    case 18: value = 17; break;	/* cmp --> subs.  */
    case 21: value = 20; break;	/* cmn --> adds.  */
    case 23: value = 22; break;	/* neg --> sub.  */
    case 25: value = 26; break;	/* cmp --> negs.  */
    case 26: value = 24; break;	/* negs --> subs.  */
    case 151: value = 150; break;	/* mov --> umov.  */
    case 153: value = 152; break;	/* mov --> ins.  */
    case 155: value = 154; break;	/* mov --> ins.  */
    case 237: value = 236; break;	/* mvn --> not.  */
    case 312: value = 311; break;	/* mov --> orr.  */
    case 383: value = 382; break;	/* sxtl --> sshll.  */
    case 385: value = 384; break;	/* sxtl2 --> sshll2.  */
    case 407: value = 406; break;	/* uxtl --> ushll.  */
    case 409: value = 408; break;	/* uxtl2 --> ushll2.  */
    case 530: value = 529; break;	/* mov --> dup.  */
    case 617: value = 616; break;	/* sxtw --> sxth.  */
    case 616: value = 615; break;	/* sxth --> sxtb.  */
    case 615: value = 618; break;	/* sxtb --> asr.  */
    case 618: value = 614; break;	/* asr --> sbfx.  */
    case 614: value = 613; break;	/* sbfx --> sbfiz.  */
    case 613: value = 612; break;	/* sbfiz --> sbfm.  */
    case 621: value = 622; break;	/* bfc --> bfxil.  */
    case 622: value = 620; break;	/* bfxil --> bfi.  */
    case 620: value = 619; break;	/* bfi --> bfm.  */
    case 627: value = 626; break;	/* uxth --> uxtb.  */
    case 626: value = 629; break;	/* uxtb --> lsr.  */
    case 629: value = 628; break;	/* lsr --> lsl.  */
    case 628: value = 625; break;	/* lsl --> ubfx.  */
    case 625: value = 624; break;	/* ubfx --> ubfiz.  */
    case 624: value = 623; break;	/* ubfiz --> ubfm.  */
    case 659: value = 658; break;	/* cset --> cinc.  */
    case 658: value = 657; break;	/* cinc --> csinc.  */
    case 662: value = 661; break;	/* csetm --> cinv.  */
    case 661: value = 660; break;	/* cinv --> csinv.  */
    case 664: value = 663; break;	/* cneg --> csneg.  */
    case 682: value = 683; break;	/* rev --> rev64.  */
    case 708: value = 707; break;	/* lsl --> lslv.  */
    case 710: value = 709; break;	/* lsr --> lsrv.  */
    case 712: value = 711; break;	/* asr --> asrv.  */
    case 714: value = 713; break;	/* ror --> rorv.  */
    case 725: value = 724; break;	/* mul --> madd.  */
    case 727: value = 726; break;	/* mneg --> msub.  */
    case 729: value = 728; break;	/* smull --> smaddl.  */
    case 731: value = 730; break;	/* smnegl --> smsubl.  */
    case 734: value = 733; break;	/* umull --> umaddl.  */
    case 736: value = 735; break;	/* umnegl --> umsubl.  */
    case 747: value = 746; break;	/* ror --> extr.  */
    case 960: value = 959; break;	/* bic --> and.  */
    case 962: value = 961; break;	/* mov --> orr.  */
    case 965: value = 964; break;	/* tst --> ands.  */
    case 970: value = 969; break;	/* uxtw --> mov.  */
    case 969: value = 968; break;	/* mov --> orr.  */
    case 972: value = 971; break;	/* mvn --> orn.  */
    case 976: value = 975; break;	/* tst --> ands.  */
    case 1102: value = 1006; break;	/* staddb --> ldaddb.  */
    case 1103: value = 1007; break;	/* staddh --> ldaddh.  */
    case 1104: value = 1008; break;	/* stadd --> ldadd.  */
    case 1105: value = 1010; break;	/* staddlb --> ldaddlb.  */
    case 1106: value = 1013; break;	/* staddlh --> ldaddlh.  */
    case 1107: value = 1016; break;	/* staddl --> ldaddl.  */
    case 1108: value = 1018; break;	/* stclrb --> ldclrb.  */
    case 1109: value = 1019; break;	/* stclrh --> ldclrh.  */
    case 1110: value = 1020; break;	/* stclr --> ldclr.  */
    case 1111: value = 1022; break;	/* stclrlb --> ldclrlb.  */
    case 1112: value = 1025; break;	/* stclrlh --> ldclrlh.  */
    case 1113: value = 1028; break;	/* stclrl --> ldclrl.  */
    case 1114: value = 1030; break;	/* steorb --> ldeorb.  */
    case 1115: value = 1031; break;	/* steorh --> ldeorh.  */
    case 1116: value = 1032; break;	/* steor --> ldeor.  */
    case 1117: value = 1034; break;	/* steorlb --> ldeorlb.  */
    case 1118: value = 1037; break;	/* steorlh --> ldeorlh.  */
    case 1119: value = 1040; break;	/* steorl --> ldeorl.  */
    case 1120: value = 1042; break;	/* stsetb --> ldsetb.  */
    case 1121: value = 1043; break;	/* stseth --> ldseth.  */
    case 1122: value = 1044; break;	/* stset --> ldset.  */
    case 1123: value = 1046; break;	/* stsetlb --> ldsetlb.  */
    case 1124: value = 1049; break;	/* stsetlh --> ldsetlh.  */
    case 1125: value = 1052; break;	/* stsetl --> ldsetl.  */
    case 1126: value = 1054; break;	/* stsmaxb --> ldsmaxb.  */
    case 1127: value = 1055; break;	/* stsmaxh --> ldsmaxh.  */
    case 1128: value = 1056; break;	/* stsmax --> ldsmax.  */
    case 1129: value = 1058; break;	/* stsmaxlb --> ldsmaxlb.  */
    case 1130: value = 1061; break;	/* stsmaxlh --> ldsmaxlh.  */
    case 1131: value = 1064; break;	/* stsmaxl --> ldsmaxl.  */
    case 1132: value = 1066; break;	/* stsminb --> ldsminb.  */
    case 1133: value = 1067; break;	/* stsminh --> ldsminh.  */
    case 1134: value = 1068; break;	/* stsmin --> ldsmin.  */
    case 1135: value = 1070; break;	/* stsminlb --> ldsminlb.  */
    case 1136: value = 1073; break;	/* stsminlh --> ldsminlh.  */
    case 1137: value = 1076; break;	/* stsminl --> ldsminl.  */
    case 1138: value = 1078; break;	/* stumaxb --> ldumaxb.  */
    case 1139: value = 1079; break;	/* stumaxh --> ldumaxh.  */
    case 1140: value = 1080; break;	/* stumax --> ldumax.  */
    case 1141: value = 1082; break;	/* stumaxlb --> ldumaxlb.  */
    case 1142: value = 1085; break;	/* stumaxlh --> ldumaxlh.  */
    case 1143: value = 1088; break;	/* stumaxl --> ldumaxl.  */
    case 1144: value = 1090; break;	/* stuminb --> lduminb.  */
    case 1145: value = 1091; break;	/* stuminh --> lduminh.  */
    case 1146: value = 1092; break;	/* stumin --> ldumin.  */
    case 1147: value = 1094; break;	/* stuminlb --> lduminlb.  */
    case 1148: value = 1097; break;	/* stuminlh --> lduminlh.  */
    case 1149: value = 1100; break;	/* stuminl --> lduminl.  */
    case 1151: value = 1150; break;	/* mov --> movn.  */
    case 1153: value = 1152; break;	/* mov --> movz.  */
    case 1194: value = 1193; break;	/* autibsp --> autibz.  */
    case 1193: value = 1192; break;	/* autibz --> autiasp.  */
    case 1192: value = 1191; break;	/* autiasp --> autiaz.  */
    case 1191: value = 1190; break;	/* autiaz --> pacibsp.  */
    case 1190: value = 1189; break;	/* pacibsp --> pacibz.  */
    case 1189: value = 1188; break;	/* pacibz --> paciasp.  */
    case 1188: value = 1187; break;	/* paciasp --> paciaz.  */
    case 1187: value = 1172; break;	/* paciaz --> psb.  */
    case 1172: value = 1171; break;	/* psb --> esb.  */
    case 1171: value = 1170; break;	/* esb --> autib1716.  */
    case 1170: value = 1169; break;	/* autib1716 --> autia1716.  */
    case 1169: value = 1168; break;	/* autia1716 --> pacib1716.  */
    case 1168: value = 1167; break;	/* pacib1716 --> pacia1716.  */
    case 1167: value = 1166; break;	/* pacia1716 --> xpaclri.  */
    case 1166: value = 1165; break;	/* xpaclri --> sevl.  */
    case 1165: value = 1164; break;	/* sevl --> sev.  */
    case 1164: value = 1163; break;	/* sev --> wfi.  */
    case 1163: value = 1162; break;	/* wfi --> wfe.  */
    case 1162: value = 1161; break;	/* wfe --> yield.  */
    case 1161: value = 1160; break;	/* yield --> csdb.  */
    case 1160: value = 1159; break;	/* csdb --> nop.  */
    case 1159: value = 1158; break;	/* nop --> hint.  */
    case 1176: value = 1175; break;	/* pssbb --> ssbb.  */
    case 1175: value = 1174; break;	/* ssbb --> dsb.  */
    case 1183: value = 1182; break;	/* tlbi --> ic.  */
    case 1182: value = 1181; break;	/* ic --> dc.  */
    case 1181: value = 1180; break;	/* dc --> at.  */
    case 1180: value = 1179; break;	/* at --> sys.  */
    case 1992: value = 1242; break;	/* bic --> and.  */
    case 1225: value = 1244; break;	/* mov --> and.  */
    case 1229: value = 1245; break;	/* movs --> ands.  */
    case 1993: value = 1280; break;	/* cmple --> cmpge.  */
    case 1996: value = 1283; break;	/* cmplt --> cmpgt.  */
    case 1994: value = 1285; break;	/* cmplo --> cmphi.  */
    case 1995: value = 1288; break;	/* cmpls --> cmphs.  */
    case 1222: value = 1310; break;	/* mov --> cpy.  */
    case 1224: value = 1311; break;	/* mov --> cpy.  */
    case 2003: value = 1227; break;	/* fmov --> mov.  */
    case 1227: value = 1312; break;	/* mov --> cpy.  */
    case 1217: value = 1324; break;	/* mov --> dup.  */
    case 1219: value = 1216; break;	/* mov --> mov.  */
    case 1216: value = 1325; break;	/* mov --> dup.  */
    case 2002: value = 1221; break;	/* fmov --> mov.  */
    case 1221: value = 1326; break;	/* mov --> dup.  */
    case 1220: value = 1327; break;	/* mov --> dupm.  */
    case 1997: value = 1329; break;	/* eon --> eor.  */
    case 1230: value = 1331; break;	/* not --> eor.  */
    case 1231: value = 1332; break;	/* nots --> eors.  */
    case 1998: value = 1337; break;	/* facle --> facge.  */
    case 1999: value = 1338; break;	/* faclt --> facgt.  */
    case 2000: value = 1351; break;	/* fcmle --> fcmge.  */
    case 2001: value = 1353; break;	/* fcmlt --> fcmgt.  */
    case 1214: value = 1359; break;	/* fmov --> fcpy.  */
    case 1213: value = 1382; break;	/* fmov --> fdup.  */
    case 1215: value = 1713; break;	/* mov --> orr.  */
    case 2004: value = 1714; break;	/* orn --> orr.  */
    case 1218: value = 1716; break;	/* mov --> orr.  */
    case 1228: value = 1717; break;	/* movs --> orrs.  */
    case 1223: value = 1779; break;	/* mov --> sel.  */
    case 1226: value = 1780; break;	/* mov --> sel.  */
    default: return NULL;
    }

  return aarch64_opcode_table + value;
}