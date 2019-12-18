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

__attribute__((used)) static int combining_lexical_Thaana(WCHAR c)
{
    enum {Thaana_Norm=0, Thaana_FILI};

   switch(c)
    {
        case 0x7A6:
        case 0x7A7:
        case 0x7A8:
        case 0x7A9:
        case 0x7AA:
        case 0x7AB:
        case 0x7AC:
        case 0x7AD:
        case 0x7AE:
        case 0x7AF: return Thaana_FILI;
        default: return Thaana_Norm;
    }
}