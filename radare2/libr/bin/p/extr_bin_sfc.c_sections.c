#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  scalar_t__ ut16 ;
struct TYPE_5__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {scalar_t__ comp_check; int rom_setup; scalar_t__ checksum; TYPE_1__ member_0; } ;
typedef  TYPE_2__ sfc_int_hdr ;
struct TYPE_7__ {int size; int /*<<< orphan*/  buf; } ;
typedef  int /*<<< orphan*/  RList ;
typedef  TYPE_3__ RBinFile ;

/* Variables and functions */
 int SFC_HDR_SIZE ; 
 int /*<<< orphan*/  addrom (int /*<<< orphan*/ *,char*,int,int,int,int) ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int r_buf_read_at (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * r_list_new () ; 

__attribute__((used)) static RList* sections(RBinFile *bf) {
	RList *ret = NULL;
	// RBinSection *ptr = NULL;
	int hdroffset = 0;
	bool is_hirom = false;
	int i = 0; //0x8000-long bank number for loops
#if THIS_IS_ALWAYS_FALSE_WTF
	if ((bf->size & 0x8000) == 0x200) {
		hdroffset = 0x200;
	}
#endif
	sfc_int_hdr sfchdr = {{0}};

	int reat = r_buf_read_at (bf->buf, 0x7FC0 + hdroffset, (ut8*)&sfchdr, SFC_HDR_SIZE);
	if (reat != SFC_HDR_SIZE) {
		eprintf ("Unable to read SFC/SNES header\n");
		return NULL;
	}

	if ( (sfchdr.comp_check != (ut16)~(sfchdr.checksum)) || ((sfchdr.rom_setup & 0x1) != 0) ){

		// if the fixed 0x33 byte or the LoROM indication are not found, then let's try interpreting the ROM as HiROM

		reat = r_buf_read_at (bf->buf, 0xFFC0 + hdroffset, (ut8*)&sfchdr, SFC_HDR_SIZE);
		if (reat != SFC_HDR_SIZE) {
			eprintf ("Unable to read SFC/SNES header\n");
			return NULL;
		}

		if ( (sfchdr.comp_check != (ut16)~(sfchdr.checksum)) || ((sfchdr.rom_setup & 0x1) != 1) ) {

			eprintf ("Cannot determine if this is a LoROM or HiROM file\n");
			return NULL;
		}
		is_hirom = true;
	}

	if (!(ret = r_list_new ())) {
		return NULL;
	}

	if (is_hirom) {
		for (i = 0; i < ((bf->size - hdroffset) / 0x8000) ; i++) {
			// XXX check integer overflow here
			addrom (ret, "ROM",i,hdroffset + i * 0x8000, 0x400000 + (i * 0x8000), 0x8000);
			if (i % 2) {
				addrom(ret, "ROM_MIRROR", i, hdroffset + i * 0x8000,(i * 0x8000), 0x8000);
			}
		}

	} else {
		for (i=0; i < ((bf->size - hdroffset)/ 0x8000) ; i++) {

			addrom(ret,"ROM",i,hdroffset + i*0x8000,0x8000 + (i*0x10000), 0x8000);
		}
	}
	return ret;
}