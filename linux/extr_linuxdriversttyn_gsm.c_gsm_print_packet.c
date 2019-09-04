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
typedef  int u8 ;

/* Variables and functions */
#define  DISC 136 
#define  DM 135 
 int PF ; 
#define  REJ 134 
#define  RNR 133 
#define  RR 132 
#define  SABM 131 
#define  UA 130 
#define  UI 129 
#define  UIH 128 
 int debug ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_info (char*,char const*,int,char) ; 

__attribute__((used)) static void gsm_print_packet(const char *hdr, int addr, int cr,
					u8 control, const u8 *data, int dlen)
{
	if (!(debug & 1))
		return;

	pr_info("%s %d) %c: ", hdr, addr, "RC"[cr]);

	switch (control & ~PF) {
	case SABM:
		pr_cont("SABM");
		break;
	case UA:
		pr_cont("UA");
		break;
	case DISC:
		pr_cont("DISC");
		break;
	case DM:
		pr_cont("DM");
		break;
	case UI:
		pr_cont("UI");
		break;
	case UIH:
		pr_cont("UIH");
		break;
	default:
		if (!(control & 0x01)) {
			pr_cont("I N(S)%d N(R)%d",
				(control & 0x0E) >> 1, (control & 0xE0) >> 5);
		} else switch (control & 0x0F) {
			case RR:
				pr_cont("RR(%d)", (control & 0xE0) >> 5);
				break;
			case RNR:
				pr_cont("RNR(%d)", (control & 0xE0) >> 5);
				break;
			case REJ:
				pr_cont("REJ(%d)", (control & 0xE0) >> 5);
				break;
			default:
				pr_cont("[%02X]", control);
		}
	}

	if (control & PF)
		pr_cont("(P)");
	else
		pr_cont("(F)");

	if (dlen) {
		int ct = 0;
		while (dlen--) {
			if (ct % 8 == 0) {
				pr_cont("\n");
				pr_debug("    ");
			}
			pr_cont("%02X ", *data++);
			ct++;
		}
	}
	pr_cont("\n");
}