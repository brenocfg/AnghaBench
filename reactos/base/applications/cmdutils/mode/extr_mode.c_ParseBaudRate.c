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
typedef  int* PDWORD ;
typedef  int /*<<< orphan*/ * PCWSTR ;

/* Variables and functions */
 int /*<<< orphan*/ * ParseNumber (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static PCWSTR
ParseBaudRate(PCWSTR argStr, PDWORD BaudRate)
{
    argStr = ParseNumber(argStr, BaudRate);
    if (!argStr) return NULL;

    /*
     * Check for Baud Rate abbreviations. This means that using
     * those values as real baud rates is impossible using MODE.
     */
    switch (*BaudRate)
    {
        /* BaudRate = 110, 150, 300, 600 */
        case 11: case 15: case 30: case 60:
            *BaudRate *= 10;
            break;

        /* BaudRate = 1200, 2400, 4800, 9600 */
        case 12: case 24: case 48: case 96:
            *BaudRate *= 100;
            break;

        case 19:
            *BaudRate = 19200;
            break;
    }

    return argStr;
}