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
typedef  int UCHAR ;
typedef  int /*<<< orphan*/  PUCHAR ;

/* Variables and functions */
 int READ_PORT_UCHAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_PORT_UCHAR (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static
UCHAR
GetFloppyType(UCHAR DriveNumber)
{
    UCHAR Data;

    WRITE_PORT_UCHAR((PUCHAR)0x70, 0x10);
    Data = READ_PORT_UCHAR((PUCHAR)0x71);

    if (DriveNumber == 0)
        return Data >> 4;
    else if (DriveNumber == 1)
        return Data & 0x0F;

    return 0;
}