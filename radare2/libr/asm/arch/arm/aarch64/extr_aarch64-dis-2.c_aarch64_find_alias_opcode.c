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
aarch64_find_alias_opcode (const aarch64_opcode *opcode)
{
  /* Use the index as the key to locate the alias opcode.  */
  int key = opcode - aarch64_opcode_table;
  int value;
  switch (key)
    {
    case 2: value = 3; break;	/* sbc --> ngc.  */
    case 4: value = 5; break;	/* sbcs --> ngcs.  */
    case 7: value = 8; break;	/* adds --> cmn.  */
    case 10: value = 11; break;	/* subs --> cmp.  */
    case 12: value = 13; break;	/* add --> mov.  */
    case 14: value = 15; break;	/* adds --> cmn.  */
    case 17: value = 18; break;	/* subs --> cmp.  */
    case 20: value = 21; break;	/* adds --> cmn.  */
    case 22: value = 23; break;	/* sub --> neg.  */
    case 24: value = 25; break;	/* subs --> cmp.  */
    case 150: value = 151; break;	/* umov --> mov.  */
    case 152: value = 153; break;	/* ins --> mov.  */
    case 154: value = 155; break;	/* ins --> mov.  */
    case 236: value = 237; break;	/* not --> mvn.  */
    case 311: value = 312; break;	/* orr --> mov.  */
    case 382: value = 383; break;	/* sshll --> sxtl.  */
    case 384: value = 385; break;	/* sshll2 --> sxtl2.  */
    case 406: value = 407; break;	/* ushll --> uxtl.  */
    case 408: value = 409; break;	/* ushll2 --> uxtl2.  */
    case 529: value = 530; break;	/* dup --> mov.  */
    case 612: value = 617; break;	/* sbfm --> sxtw.  */
    case 619: value = 621; break;	/* bfm --> bfc.  */
    case 623: value = 627; break;	/* ubfm --> uxth.  */
    case 657: value = 659; break;	/* csinc --> cset.  */
    case 660: value = 662; break;	/* csinv --> csetm.  */
    case 663: value = 664; break;	/* csneg --> cneg.  */
    case 682: value = 682; break;	/* rev --> rev.  */
    case 707: value = 708; break;	/* lslv --> lsl.  */
    case 709: value = 710; break;	/* lsrv --> lsr.  */
    case 711: value = 712; break;	/* asrv --> asr.  */
    case 713: value = 714; break;	/* rorv --> ror.  */
    case 724: value = 725; break;	/* madd --> mul.  */
    case 726: value = 727; break;	/* msub --> mneg.  */
    case 728: value = 729; break;	/* smaddl --> smull.  */
    case 730: value = 731; break;	/* smsubl --> smnegl.  */
    case 733: value = 734; break;	/* umaddl --> umull.  */
    case 735: value = 736; break;	/* umsubl --> umnegl.  */
    case 746: value = 747; break;	/* extr --> ror.  */
    case 959: value = 960; break;	/* and --> bic.  */
    case 961: value = 962; break;	/* orr --> mov.  */
    case 964: value = 965; break;	/* ands --> tst.  */
    case 968: value = 970; break;	/* orr --> uxtw.  */
    case 971: value = 972; break;	/* orn --> mvn.  */
    case 975: value = 976; break;	/* ands --> tst.  */
    case 1006: value = 1102; break;	/* ldaddb --> staddb.  */
    case 1007: value = 1103; break;	/* ldaddh --> staddh.  */
    case 1008: value = 1104; break;	/* ldadd --> stadd.  */
    case 1010: value = 1105; break;	/* ldaddlb --> staddlb.  */
    case 1013: value = 1106; break;	/* ldaddlh --> staddlh.  */
    case 1016: value = 1107; break;	/* ldaddl --> staddl.  */
    case 1018: value = 1108; break;	/* ldclrb --> stclrb.  */
    case 1019: value = 1109; break;	/* ldclrh --> stclrh.  */
    case 1020: value = 1110; break;	/* ldclr --> stclr.  */
    case 1022: value = 1111; break;	/* ldclrlb --> stclrlb.  */
    case 1025: value = 1112; break;	/* ldclrlh --> stclrlh.  */
    case 1028: value = 1113; break;	/* ldclrl --> stclrl.  */
    case 1030: value = 1114; break;	/* ldeorb --> steorb.  */
    case 1031: value = 1115; break;	/* ldeorh --> steorh.  */
    case 1032: value = 1116; break;	/* ldeor --> steor.  */
    case 1034: value = 1117; break;	/* ldeorlb --> steorlb.  */
    case 1037: value = 1118; break;	/* ldeorlh --> steorlh.  */
    case 1040: value = 1119; break;	/* ldeorl --> steorl.  */
    case 1042: value = 1120; break;	/* ldsetb --> stsetb.  */
    case 1043: value = 1121; break;	/* ldseth --> stseth.  */
    case 1044: value = 1122; break;	/* ldset --> stset.  */
    case 1046: value = 1123; break;	/* ldsetlb --> stsetlb.  */
    case 1049: value = 1124; break;	/* ldsetlh --> stsetlh.  */
    case 1052: value = 1125; break;	/* ldsetl --> stsetl.  */
    case 1054: value = 1126; break;	/* ldsmaxb --> stsmaxb.  */
    case 1055: value = 1127; break;	/* ldsmaxh --> stsmaxh.  */
    case 1056: value = 1128; break;	/* ldsmax --> stsmax.  */
    case 1058: value = 1129; break;	/* ldsmaxlb --> stsmaxlb.  */
    case 1061: value = 1130; break;	/* ldsmaxlh --> stsmaxlh.  */
    case 1064: value = 1131; break;	/* ldsmaxl --> stsmaxl.  */
    case 1066: value = 1132; break;	/* ldsminb --> stsminb.  */
    case 1067: value = 1133; break;	/* ldsminh --> stsminh.  */
    case 1068: value = 1134; break;	/* ldsmin --> stsmin.  */
    case 1070: value = 1135; break;	/* ldsminlb --> stsminlb.  */
    case 1073: value = 1136; break;	/* ldsminlh --> stsminlh.  */
    case 1076: value = 1137; break;	/* ldsminl --> stsminl.  */
    case 1078: value = 1138; break;	/* ldumaxb --> stumaxb.  */
    case 1079: value = 1139; break;	/* ldumaxh --> stumaxh.  */
    case 1080: value = 1140; break;	/* ldumax --> stumax.  */
    case 1082: value = 1141; break;	/* ldumaxlb --> stumaxlb.  */
    case 1085: value = 1142; break;	/* ldumaxlh --> stumaxlh.  */
    case 1088: value = 1143; break;	/* ldumaxl --> stumaxl.  */
    case 1090: value = 1144; break;	/* lduminb --> stuminb.  */
    case 1091: value = 1145; break;	/* lduminh --> stuminh.  */
    case 1092: value = 1146; break;	/* ldumin --> stumin.  */
    case 1094: value = 1147; break;	/* lduminlb --> stuminlb.  */
    case 1097: value = 1148; break;	/* lduminlh --> stuminlh.  */
    case 1100: value = 1149; break;	/* lduminl --> stuminl.  */
    case 1150: value = 1151; break;	/* movn --> mov.  */
    case 1152: value = 1153; break;	/* movz --> mov.  */
    case 1158: value = 1194; break;	/* hint --> autibsp.  */
    case 1174: value = 1176; break;	/* dsb --> pssbb.  */
    case 1179: value = 1183; break;	/* sys --> tlbi.  */
    case 1242: value = 1992; break;	/* and --> bic.  */
    case 1244: value = 1225; break;	/* and --> mov.  */
    case 1245: value = 1229; break;	/* ands --> movs.  */
    case 1280: value = 1993; break;	/* cmpge --> cmple.  */
    case 1283: value = 1996; break;	/* cmpgt --> cmplt.  */
    case 1285: value = 1994; break;	/* cmphi --> cmplo.  */
    case 1288: value = 1995; break;	/* cmphs --> cmpls.  */
    case 1310: value = 1222; break;	/* cpy --> mov.  */
    case 1311: value = 1224; break;	/* cpy --> mov.  */
    case 1312: value = 2003; break;	/* cpy --> fmov.  */
    case 1324: value = 1217; break;	/* dup --> mov.  */
    case 1325: value = 1219; break;	/* dup --> mov.  */
    case 1326: value = 2002; break;	/* dup --> fmov.  */
    case 1327: value = 1220; break;	/* dupm --> mov.  */
    case 1329: value = 1997; break;	/* eor --> eon.  */
    case 1331: value = 1230; break;	/* eor --> not.  */
    case 1332: value = 1231; break;	/* eors --> nots.  */
    case 1337: value = 1998; break;	/* facge --> facle.  */
    case 1338: value = 1999; break;	/* facgt --> faclt.  */
    case 1351: value = 2000; break;	/* fcmge --> fcmle.  */
    case 1353: value = 2001; break;	/* fcmgt --> fcmlt.  */
    case 1359: value = 1214; break;	/* fcpy --> fmov.  */
    case 1382: value = 1213; break;	/* fdup --> fmov.  */
    case 1713: value = 1215; break;	/* orr --> mov.  */
    case 1714: value = 2004; break;	/* orr --> orn.  */
    case 1716: value = 1218; break;	/* orr --> mov.  */
    case 1717: value = 1228; break;	/* orrs --> movs.  */
    case 1779: value = 1223; break;	/* sel --> mov.  */
    case 1780: value = 1226; break;	/* sel --> mov.  */
    default: return NULL;
    }

  return aarch64_opcode_table + value;
}