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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 unsigned int CV_AMD64_CS ; 
 unsigned int CV_AMD64_CTRL ; 
 unsigned int CV_AMD64_DS ; 
 unsigned int CV_AMD64_EFLAGS ; 
 unsigned int CV_AMD64_ES ; 
 unsigned int CV_AMD64_FS ; 
 unsigned int CV_AMD64_GS ; 
 unsigned int CV_AMD64_LDTR ; 
 unsigned int CV_AMD64_MXCSR ; 
 unsigned int CV_AMD64_R10 ; 
 unsigned int CV_AMD64_R11 ; 
 unsigned int CV_AMD64_R12 ; 
 unsigned int CV_AMD64_R13 ; 
 unsigned int CV_AMD64_R14 ; 
 unsigned int CV_AMD64_R15 ; 
 unsigned int CV_AMD64_R8 ; 
 unsigned int CV_AMD64_R9 ; 
 unsigned int CV_AMD64_RAX ; 
 unsigned int CV_AMD64_RBP ; 
 unsigned int CV_AMD64_RBX ; 
 unsigned int CV_AMD64_RCX ; 
 unsigned int CV_AMD64_RDI ; 
 unsigned int CV_AMD64_RDX ; 
 unsigned int CV_AMD64_RIP ; 
 unsigned int CV_AMD64_RSI ; 
 unsigned int CV_AMD64_RSP ; 
 unsigned int CV_AMD64_SS ; 
 unsigned int CV_AMD64_ST0 ; 
 unsigned int CV_AMD64_STAT ; 
 unsigned int CV_AMD64_TR ; 
 unsigned int CV_AMD64_XMM0 ; 
 unsigned int CV_AMD64_XMM8 ; 
 int /*<<< orphan*/  FIXME (char*,unsigned int) ; 

__attribute__((used)) static unsigned x86_64_map_dwarf_register(unsigned regno, BOOL eh_frame)
{
    unsigned    reg;

    if (regno >= 17 && regno <= 24)
        reg = CV_AMD64_XMM0 + regno - 17;
    else if (regno >= 25 && regno <= 32)
        reg = CV_AMD64_XMM8 + regno - 25;
    else if (regno >= 33 && regno <= 40)
        reg = CV_AMD64_ST0 + regno - 33;
    else switch (regno)
    {
    case  0: reg = CV_AMD64_RAX;    break;
    case  1: reg = CV_AMD64_RDX;    break;
    case  2: reg = CV_AMD64_RCX;    break;
    case  3: reg = CV_AMD64_RBX;    break;
    case  4: reg = CV_AMD64_RSI;    break;
    case  5: reg = CV_AMD64_RDI;    break;
    case  6: reg = CV_AMD64_RBP;    break;
    case  7: reg = CV_AMD64_RSP;    break;
    case  8: reg = CV_AMD64_R8;     break;
    case  9: reg = CV_AMD64_R9;     break;
    case 10: reg = CV_AMD64_R10;    break;
    case 11: reg = CV_AMD64_R11;    break;
    case 12: reg = CV_AMD64_R12;    break;
    case 13: reg = CV_AMD64_R13;    break;
    case 14: reg = CV_AMD64_R14;    break;
    case 15: reg = CV_AMD64_R15;    break;
    case 16: reg = CV_AMD64_RIP;    break;
    case 49: reg = CV_AMD64_EFLAGS; break;
    case 50: reg = CV_AMD64_ES;     break;
    case 51: reg = CV_AMD64_CS;     break;
    case 52: reg = CV_AMD64_SS;     break;
    case 53: reg = CV_AMD64_DS;     break;
    case 54: reg = CV_AMD64_FS;     break;
    case 55: reg = CV_AMD64_GS;     break;
    case 62: reg = CV_AMD64_TR;     break;
    case 63: reg = CV_AMD64_LDTR;   break;
    case 64: reg = CV_AMD64_MXCSR;  break;
    case 65: reg = CV_AMD64_CTRL;   break;
    case 66: reg = CV_AMD64_STAT;   break;
/*
 * 56-57 reserved
 * 58 %fs.base
 * 59 %gs.base
 * 60-61 reserved
 */
    default:
        FIXME("Don't know how to map register %d\n", regno);
        return 0;
    }
    return reg;
}