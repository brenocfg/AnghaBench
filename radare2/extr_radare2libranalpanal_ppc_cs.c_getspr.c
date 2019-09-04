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
typedef  int ut32 ;
struct Getarg {int dummy; } ;
typedef  int /*<<< orphan*/  cspr ;

/* Variables and functions */
#define  SPR_HID0 133 
#define  SPR_HID1 132 
#define  SPR_HID2 131 
#define  SPR_HID4 130 
#define  SPR_HID5 129 
#define  SPR_HID6 128 
 int getarg (struct Getarg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static const char* getspr(struct Getarg *gop, int n) {
	static char cspr[16];
	ut32 spr = 0;
	if (n < 0 || n >= 8) {
		return NULL;
	}
	spr = getarg (gop, 0);
	switch (spr) {
	case SPR_HID0:
		return "hid0";
	case SPR_HID1:
		return "hid1";
	case SPR_HID2:
		return "hid2";
	case SPR_HID4:
		return "hid4";
	case SPR_HID5:
		return "hid5";
	case SPR_HID6:
		return "hid6";
	default:
		snprintf (cspr, sizeof (cspr), "spr_%u", spr);
		break;
	}
	return cspr;
}