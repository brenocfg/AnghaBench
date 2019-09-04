#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  scalar_t__ ut32 ;
typedef  int /*<<< orphan*/  hdr ;
struct TYPE_5__ {int /*<<< orphan*/  buf; } ;
struct TYPE_4__ {int /*<<< orphan*/  CountryCode; int /*<<< orphan*/  ModemCode; int /*<<< orphan*/  SramCode; int /*<<< orphan*/  Peripherials; int /*<<< orphan*/  CheckSum; int /*<<< orphan*/  ProductCode; int /*<<< orphan*/  OverseasName; int /*<<< orphan*/  DomesticName; int /*<<< orphan*/  CopyRights; scalar_t__ RamEnd; scalar_t__ RamStart; scalar_t__ RomEnd; scalar_t__ RomStart; } ;
typedef  TYPE_1__ SMD_Header ;
typedef  int /*<<< orphan*/  RList ;
typedef  TYPE_2__ RBinFile ;

/* Variables and functions */
 int /*<<< orphan*/  addsym (int /*<<< orphan*/ *,char const*,scalar_t__) ; 
 int /*<<< orphan*/  eprintf (char*,scalar_t__) ; 
 int /*<<< orphan*/  free ; 
 int r_buf_read_at (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * r_list_newf (int /*<<< orphan*/ ) ; 
 scalar_t__ r_read_be32 (scalar_t__*) ; 
 int /*<<< orphan*/  showstr (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static RList *symbols(RBinFile *bf) {
	RList *ret = NULL;
	const char *name = NULL;
	int i;

	if (!(ret = r_list_newf (free))) {
		return NULL;
	}
	SMD_Header hdr;
	int left = r_buf_read_at (bf->buf, 0x100, (ut8*)&hdr, sizeof (hdr));
	if (left < sizeof (SMD_Header)) {
		return NULL;
	}
	// TODO: store all this stuff in SDB
	addsym (ret, "rom_start", r_read_be32 (&hdr.RomStart));
	addsym (ret, "rom_end", r_read_be32 (&hdr.RomEnd));
	addsym (ret, "ram_start", r_read_be32 (&hdr.RamStart));
	addsym (ret, "ram_end", r_read_be32 (&hdr.RamEnd));
	showstr ("Copyright", hdr.CopyRights, 32);
	showstr ("DomesticName", hdr.DomesticName, 48);
	showstr ("OverseasName", hdr.OverseasName, 48);
	showstr ("ProductCode", hdr.ProductCode, 14);
	eprintf ("Checksum: 0x%04x\n", (ut32) hdr.CheckSum);
	showstr ("Peripherials", hdr.Peripherials, 16);
	showstr ("SramCode", hdr.SramCode, 12);
	showstr ("ModemCode", hdr.ModemCode, 12);
	showstr ("CountryCode", hdr.CountryCode, 16);
	ut32 vtable[64];
	r_buf_read_at (bf->buf, 0, (ut8*)&vtable, sizeof (ut32) * 64);
	/* parse vtable */
	for (i = 0; i < 64; i++) {
		switch (i) {
		case 0: name = "SSP"; break;
		case 1: name = "Reset"; break;
		case 2: name = "BusErr"; break;
		case 3: name = "AdrErr"; break;
		case 4: name = "InvOpCode"; break;
		case 5: name = "DivBy0"; break;
		case 6: name = "Check"; break;
		case 7: name = "TrapV"; break;
		case 8: name = "GPF"; break;
		case 9: name = "Trace"; break;
		case 10: name = "Reserv0"; break;
		case 11: name = "Reserv1"; break;
		case 12: name = "Reserv2"; break;
		case 13: name = "Reserv3"; break;
		case 14: name = "Reserv4"; break;
		case 15: name = "BadInt"; break;
		case 16: name = "Reserv10"; break;
		case 17: name = "Reserv11"; break;
		case 18: name = "Reserv12"; break;
		case 19: name = "Reserv13"; break;
		case 20: name = "Reserv14"; break;
		case 21: name = "Reserv15"; break;
		case 22: name = "Reserv16"; break;
		case 23: name = "Reserv17"; break;
		case 24: name = "BadIRQ"; break;
		case 25: name = "IRQ1"; break;
		case 26: name = "EXT"; break;
		case 27: name = "IRQ3"; break;
		case 28: name = "HBLANK"; break;
		case 29: name = "IRQ5"; break;
		case 30: name = "VBLANK"; break;
		case 31: name = "IRQ7"; break;
		case 32: name = "Trap0"; break;
		case 33: name = "Trap1"; break;
		case 34: name = "Trap2"; break;
		case 35: name = "Trap3"; break;
		case 36: name = "Trap4"; break;
		case 37: name = "Trap5"; break;
		case 38: name = "Trap6"; break;
		case 39: name = "Trap7"; break;
		case 40: name = "Trap8"; break;
		case 41: name = "Trap9"; break;
		case 42: name = "Trap10"; break;
		case 43: name = "Trap11"; break;
		case 44: name = "Trap12"; break;
		case 45: name = "Trap13"; break;
		case 46: name = "Trap14"; break;
		case 47: name = "Trap15"; break;
		case 48: name = "Reserv30"; break;
		case 49: name = "Reserv31"; break;
		case 50: name = "Reserv32"; break;
		case 51: name = "Reserv33"; break;
		case 52: name = "Reserv34"; break;
		case 53: name = "Reserv35"; break;
		case 54: name = "Reserv36"; break;
		case 55: name = "Reserv37"; break;
		case 56: name = "Reserv38"; break;
		case 57: name = "Reserv39"; break;
		case 58: name = "Reserv3A"; break;
		case 59: name = "Reserv3B"; break;
		case 60: name = "Reserv3C"; break;
		case 61: name = "Reserv3D"; break;
		case 62: name = "Reserv3E"; break;
		case 63: name = "Reserv3F"; break;
		default: name = NULL;
		}
		if (name && vtable[i]) {
			ut32 addr = r_read_be32 (&vtable[i]);
			addsym (ret, name, addr);
		}
	}
	return ret;
}