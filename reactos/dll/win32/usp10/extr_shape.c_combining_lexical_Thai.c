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
typedef  int WCHAR ;

/* Variables and functions */

__attribute__((used)) static int combining_lexical_Thai(WCHAR c)
{
    enum {Thai_Norm=0, Thai_ABOVE1, Thai_ABOVE2, Thai_ABOVE3, Thai_ABOVE4, Thai_BELOW1, Thai_BELOW2, Thai_AM};

   switch(c)
    {
        case 0xE31:
        case 0xE34:
        case 0xE35:
        case 0xE36:
        case 0xE37: return Thai_ABOVE1;
        case 0xE47:
        case 0xE4D: return Thai_ABOVE2;
        case 0xE48:
        case 0xE49:
        case 0xE4A:
        case 0xE4B: return Thai_ABOVE3;
        case 0xE4C:
        case 0xE4E: return Thai_ABOVE4;
        case 0xE38:
        case 0xE39: return Thai_BELOW1;
        case 0xE3A: return Thai_BELOW2;
        case 0xE33: return Thai_AM;
        default: return Thai_Norm;
    }
}