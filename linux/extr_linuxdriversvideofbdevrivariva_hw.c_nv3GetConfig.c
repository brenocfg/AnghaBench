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
struct TYPE_3__ {int RamBandwidthKBytesPerSec; int RamAmountKBytes; int CrystalFreqKHz; int VBlankBit; int MaxVClockFreqKHz; int /*<<< orphan*/  LockUnlock; int /*<<< orphan*/  SetSurfaces3D; int /*<<< orphan*/  SetSurfaces2D; int /*<<< orphan*/  SetStartAddress; int /*<<< orphan*/  UnloadStateExt; int /*<<< orphan*/  LoadStateExt; int /*<<< orphan*/  ShowHideCursor; int /*<<< orphan*/  Busy; int /*<<< orphan*/ * PRAMIN; int /*<<< orphan*/ * CURSOR; int /*<<< orphan*/ * PEXTDEV; int /*<<< orphan*/ * PFB; int /*<<< orphan*/ * PMC; } ;
typedef  TYPE_1__ RIVA_HW_INST ;

/* Variables and functions */
 int /*<<< orphan*/  LoadStateExt ; 
 int NV_RD32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SetStartAddress3 ; 
 int /*<<< orphan*/  ShowHideCursor ; 
 int /*<<< orphan*/  UnloadStateExt ; 
 int /*<<< orphan*/  nv3Busy ; 
 int /*<<< orphan*/  nv3LockUnlock ; 
 int /*<<< orphan*/  nv3SetSurfaces2D ; 
 int /*<<< orphan*/  nv3SetSurfaces3D ; 

__attribute__((used)) static void nv3GetConfig
(
    RIVA_HW_INST *chip
)
{
    /*
     * Fill in chip configuration.
     */
    if (NV_RD32(&chip->PFB[0x00000000/4], 0) & 0x00000020)
    {
        if (((NV_RD32(chip->PMC, 0x00000000) & 0xF0) == 0x20)
         && ((NV_RD32(chip->PMC, 0x00000000) & 0x0F) >= 0x02))
        {        
            /*
             * SDRAM 128 ZX.
             */
            chip->RamBandwidthKBytesPerSec = 800000;
            switch (NV_RD32(chip->PFB, 0x00000000) & 0x03)
            {
                case 2:
                    chip->RamAmountKBytes = 1024 * 4;
                    break;
                case 1:
                    chip->RamAmountKBytes = 1024 * 2;
                    break;
                default:
                    chip->RamAmountKBytes = 1024 * 8;
                    break;
            }
        }            
        else            
        {
            chip->RamBandwidthKBytesPerSec = 1000000;
            chip->RamAmountKBytes          = 1024 * 8;
        }            
    }
    else
    {
        /*
         * SGRAM 128.
         */
        chip->RamBandwidthKBytesPerSec = 1000000;
        switch (NV_RD32(chip->PFB, 0x00000000) & 0x00000003)
        {
            case 0:
                chip->RamAmountKBytes = 1024 * 8;
                break;
            case 2:
                chip->RamAmountKBytes = 1024 * 4;
                break;
            default:
                chip->RamAmountKBytes = 1024 * 2;
                break;
        }
    }        
    chip->CrystalFreqKHz   = (NV_RD32(chip->PEXTDEV, 0x00000000) & 0x00000040) ? 14318 : 13500;
    chip->CURSOR           = &(chip->PRAMIN[0x00008000/4 - 0x0800/4]);
    chip->VBlankBit        = 0x00000100;
    chip->MaxVClockFreqKHz = 256000;
    /*
     * Set chip functions.
     */
    chip->Busy            = nv3Busy;
    chip->ShowHideCursor  = ShowHideCursor;
    chip->LoadStateExt    = LoadStateExt;
    chip->UnloadStateExt  = UnloadStateExt;
    chip->SetStartAddress = SetStartAddress3;
    chip->SetSurfaces2D   = nv3SetSurfaces2D;
    chip->SetSurfaces3D   = nv3SetSurfaces3D;
    chip->LockUnlock      = nv3LockUnlock;
}