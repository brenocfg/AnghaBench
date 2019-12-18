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
struct TYPE_3__ {int l; } ;
typedef  TYPE_1__* PMIDIALLOC ;
typedef  int BYTE ;

/* Variables and functions */

__attribute__((used)) static int GetMidiLength(PMIDIALLOC pClient, BYTE b)
{
    if (b >= 0xF8)
    {
        // Realtime message - leave running status
        return 1; // Write one byte
    }

    switch (b)
    {
        case 0xF0: case 0xF4: case 0xF5: case 0xF6: case 0xF7:
            pClient->l = 1;
            return pClient->l;

        case 0xF1: case 0xF3:
            pClient->l = 2;
            return pClient->l;

        case 0xF2:
            pClient->l = 3;
            return pClient->l;
    }

    switch (b & 0xF0)
    {
        case 0x80: case 0x90: case 0xA0: case 0xB0: case 0xE0:
            pClient->l = 3;
            return pClient->l;

        case 0xC0: case 0xD0:
            pClient->l = 2;
            return pClient->l;
    }

    return (pClient->l - 1); // uses previous value if data byte (running status)
}