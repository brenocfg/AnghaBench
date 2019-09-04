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
psr_name (int regno)
{
  switch (regno)
    {
    case 0x0: return "APSR";
    case 0x1: return "IAPSR";
    case 0x2: return "EAPSR";
    case 0x3: return "PSR";
    case 0x5: return "IPSR";
    case 0x6: return "EPSR";
    case 0x7: return "IEPSR";
    case 0x8: return "MSP";
    case 0x9: return "PSP";
    case 0xa: return "MSPLIM";
    case 0xb: return "PSPLIM";
    case 0x10: return "PRIMASK";
    case 0x11: return "BASEPRI";
    case 0x12: return "BASEPRI_MAX";
    case 0x13: return "FAULTMASK";
    case 0x14: return "CONTROL";
    case 0x88: return "MSP_NS";
    case 0x89: return "PSP_NS";
    case 0x8a: return "MSPLIM_NS";
    case 0x8b: return "PSPLIM_NS";
    case 0x90: return "PRIMASK_NS";
    case 0x91: return "BASEPRI_NS";
    case 0x93: return "FAULTMASK_NS";
    case 0x94: return "CONTROL_NS";
    case 0x98: return "SP_NS";
    default: return "<unknown>";
    }
}