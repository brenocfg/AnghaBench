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
struct TYPE_3__ {int /*<<< orphan*/ * uuid; } ;
typedef  TYPE_1__ SymbolsHeader ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*,...) ; 

__attribute__((used)) static void printSymbolsHeader(SymbolsHeader sh) {
	// eprintf ("0x%08x  version  0x%x\n", 4, sh.version);
	eprintf ("0x%08x  uuid     ", 24);
	int i;
	for (i = 0; i < 16; i++) {
		eprintf ("%02x", sh.uuid[i]);
	}
	eprintf ("\n");
	// parse header
	// eprintf ("0x%08x  unknown  0x%x\n", 0x28, sh.unk0); //r_read_le32 (b+ 0x28));
	// eprintf ("0x%08x  unknown  0x%x\n", 0x2c, sh.unk1); //r_read_le16 (b+ 0x2c));
	// eprintf ("0x%08x  slotsize %d\n", 0x2e, sh.slotsize); // r_read_le16 (b+ 0x2e));
}