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

/* Variables and functions */

__attribute__((used)) static const char *
banked_regname (unsigned reg)
{
  switch (reg)
    {
      case 15: return "CPSR";
      case 32: return "R8_usr";
      case 33: return "R9_usr";
      case 34: return "R10_usr";
      case 35: return "R11_usr";
      case 36: return "R12_usr";
      case 37: return "SP_usr";
      case 38: return "LR_usr";
      case 40: return "R8_fiq";
      case 41: return "R9_fiq";
      case 42: return "R10_fiq";
      case 43: return "R11_fiq";
      case 44: return "R12_fiq";
      case 45: return "SP_fiq";
      case 46: return "LR_fiq";
      case 48: return "LR_irq";
      case 49: return "SP_irq";
      case 50: return "LR_svc";
      case 51: return "SP_svc";
      case 52: return "LR_abt";
      case 53: return "SP_abt";
      case 54: return "LR_und";
      case 55: return "SP_und";
      case 60: return "LR_mon";
      case 61: return "SP_mon";
      case 62: return "ELR_hyp";
      case 63: return "SP_hyp";
      case 79: return "SPSR";
      case 110: return "SPSR_fiq";
      case 112: return "SPSR_irq";
      case 114: return "SPSR_svc";
      case 116: return "SPSR_abt";
      case 118: return "SPSR_und";
      case 124: return "SPSR_mon";
      case 126: return "SPSR_hyp";
      default: return NULL;
    }
}