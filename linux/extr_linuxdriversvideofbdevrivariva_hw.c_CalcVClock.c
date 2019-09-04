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
struct TYPE_3__ {int CrystalFreqKHz; scalar_t__ Architecture; unsigned int MaxVClockFreqKHz; } ;
typedef  TYPE_1__ RIVA_HW_INST ;

/* Variables and functions */
 scalar_t__ NV_ARCH_03 ; 

__attribute__((used)) static int CalcVClock
(
    int           clockIn,
    int          *clockOut,
    int          *mOut,
    int          *nOut,
    int          *pOut,
    RIVA_HW_INST *chip
)
{
    unsigned lowM, highM, highP;
    unsigned DeltaNew, DeltaOld;
    unsigned VClk, Freq;
    unsigned M, N, P;
    
    DeltaOld = 0xFFFFFFFF;

    VClk     = (unsigned)clockIn;
    
    if (chip->CrystalFreqKHz == 13500)
    {
        lowM  = 7;
        highM = 13 - (chip->Architecture == NV_ARCH_03);
    }
    else
    {
        lowM  = 8;
        highM = 14 - (chip->Architecture == NV_ARCH_03);
    }                      

    highP = 4 - (chip->Architecture == NV_ARCH_03);
    for (P = 0; P <= highP; P ++)
    {
        Freq = VClk << P;
        if ((Freq >= 128000) && (Freq <= chip->MaxVClockFreqKHz))
        {
            for (M = lowM; M <= highM; M++)
            {
                N    = (VClk << P) * M / chip->CrystalFreqKHz;
                if(N <= 255) {
                Freq = (chip->CrystalFreqKHz * N / M) >> P;
                if (Freq > VClk)
                    DeltaNew = Freq - VClk;
                else
                    DeltaNew = VClk - Freq;
                if (DeltaNew < DeltaOld)
                {
                    *mOut     = M;
                    *nOut     = N;
                    *pOut     = P;
                    *clockOut = Freq;
                    DeltaOld  = DeltaNew;
                }
            }
        }
    }
    }

    /* non-zero: M/N/P/clock values assigned.  zero: error (not set) */
    return (DeltaOld != 0xFFFFFFFF);
}