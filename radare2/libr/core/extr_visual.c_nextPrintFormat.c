#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int printidx; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 size_t PRINT_3_FORMATS ; 
 size_t PRINT_4_FORMATS ; 
 size_t PRINT_5_FORMATS ; 
 size_t PRINT_HEX_FORMATS ; 
 size_t R_ABS (int /*<<< orphan*/ ) ; 
#define  R_CORE_VISUAL_MODE_CD 132 
#define  R_CORE_VISUAL_MODE_DB 131 
#define  R_CORE_VISUAL_MODE_OV 130 
#define  R_CORE_VISUAL_MODE_PD 129 
#define  R_CORE_VISUAL_MODE_PX 128 
 int /*<<< orphan*/  current3format ; 
 int /*<<< orphan*/  current4format ; 
 int /*<<< orphan*/  current5format ; 
 size_t currentFormat ; 
 int /*<<< orphan*/  disMode ; 
 int /*<<< orphan*/  hexMode ; 
 int /*<<< orphan*/ * print3Formats ; 
 int /*<<< orphan*/ * print4Formats ; 
 int /*<<< orphan*/ * print5Formats ; 
 int /*<<< orphan*/ * printHexFormats ; 
 int /*<<< orphan*/ * printfmtSingle ; 
 int /*<<< orphan*/  r_core_visual_applyDisMode (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_core_visual_applyHexMode (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rotateAsmemu (TYPE_1__*) ; 

__attribute__((used)) static void nextPrintFormat(RCore *core) {
	switch (core->printidx) {
	case R_CORE_VISUAL_MODE_PX: // 0 // xc
		r_core_visual_applyHexMode (core, ++hexMode);
		printfmtSingle[0] = printHexFormats[R_ABS(hexMode) % PRINT_HEX_FORMATS];
		break;
	case R_CORE_VISUAL_MODE_PD: // pd
		r_core_visual_applyDisMode (core, ++disMode);
		printfmtSingle[1] = rotateAsmemu (core);
		break;
	case R_CORE_VISUAL_MODE_DB: // debugger
		r_core_visual_applyDisMode (core, ++disMode);
		printfmtSingle[1] = rotateAsmemu (core);
		current3format++;
		currentFormat = R_ABS (current3format) % PRINT_3_FORMATS;
		printfmtSingle[2] = print3Formats[currentFormat];
		break;
	case R_CORE_VISUAL_MODE_OV: // overview
		current4format++;
		currentFormat = R_ABS (current4format) % PRINT_4_FORMATS;
		printfmtSingle[3] = print4Formats[currentFormat];
		break;
	case R_CORE_VISUAL_MODE_CD: // code
		current5format++;
		currentFormat = R_ABS (current5format) % PRINT_5_FORMATS;
		printfmtSingle[4] = print5Formats[currentFormat];
		break;
	}
}