#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_9__ {int es; int bp; } ;
struct TYPE_8__ {int /*<<< orphan*/  bh; } ;
struct TYPE_7__ {int eax; } ;
struct TYPE_10__ {TYPE_3__ w; TYPE_2__ b; TYPE_1__ d; } ;
typedef  TYPE_4__ REGS ;
typedef  int* PULONG ;

/* Variables and functions */
 int /*<<< orphan*/  Int386 (int,TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  ROM_8x14CharacterFont ; 
 int /*<<< orphan*/  ROM_8x16Font ; 
 int /*<<< orphan*/  ROM_8x8DoubleDotFontHi ; 
 int /*<<< orphan*/  ROM_8x8DoubleDotFontLo ; 
 int /*<<< orphan*/  ROM_AlphaAlternate ; 
 int /*<<< orphan*/  ROM_Alternate9x16Font ; 

VOID
PcVideoGetFontsFromFirmware(PULONG RomFontPointers)
{
    REGS BiosRegs;

    /* Get the address of the BIOS ROM fonts.
       Int 10h, AX=1130h, BH = pointer specifier
       returns: es:bp = address */
    BiosRegs.d.eax = 0x1130;
    BiosRegs.b.bh = ROM_8x14CharacterFont;
    Int386(0x10, &BiosRegs, &BiosRegs);
    RomFontPointers[0] = BiosRegs.w.es << 4 | BiosRegs.w.bp;

    BiosRegs.b.bh = ROM_8x8DoubleDotFontLo;
    Int386(0x10, &BiosRegs, &BiosRegs);
    RomFontPointers[1] = BiosRegs.w.es << 16 | BiosRegs.w.bp;

    BiosRegs.b.bh = ROM_8x8DoubleDotFontHi;
    Int386(0x10, &BiosRegs, &BiosRegs);
    RomFontPointers[2] = BiosRegs.w.es << 16 | BiosRegs.w.bp;

    BiosRegs.b.bh = ROM_AlphaAlternate;
    Int386(0x10, &BiosRegs, &BiosRegs);
    RomFontPointers[3] = BiosRegs.w.es << 16 | BiosRegs.w.bp;

    BiosRegs.b.bh = ROM_8x16Font;
    Int386(0x10, &BiosRegs, &BiosRegs);
    RomFontPointers[4] = BiosRegs.w.es << 16 | BiosRegs.w.bp;

    BiosRegs.b.bh = ROM_Alternate9x16Font;
    Int386(0x10, &BiosRegs, &BiosRegs);
    RomFontPointers[5] = BiosRegs.w.es << 16 | BiosRegs.w.bp;
}