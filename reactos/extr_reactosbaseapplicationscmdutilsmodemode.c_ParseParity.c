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
typedef  int /*<<< orphan*/ * PCWSTR ;
typedef  int /*<<< orphan*/ * PBYTE ;

/* Variables and functions */
 int /*<<< orphan*/  EVENPARITY ; 
 int /*<<< orphan*/  MARKPARITY ; 
 int /*<<< orphan*/  NOPARITY ; 
 int /*<<< orphan*/  ODDPARITY ; 
 int /*<<< orphan*/  SPACEPARITY ; 
 int towupper (int /*<<< orphan*/ ) ; 

__attribute__((used)) static PCWSTR
ParseParity(PCWSTR argStr, PBYTE Parity)
{
    switch (towupper(*argStr++))
    {
        case L'N':
            *Parity = NOPARITY;
            break;

        case L'O':
            *Parity = ODDPARITY;
            break;

        case L'E':
            *Parity = EVENPARITY;
            break;

        case L'M':
            *Parity = MARKPARITY;
            break;

        case L'S':
            *Parity = SPACEPARITY;
            break;

        default:
            return NULL;
    }

    return argStr;
}