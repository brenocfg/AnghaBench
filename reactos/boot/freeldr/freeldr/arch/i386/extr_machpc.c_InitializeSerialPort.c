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
typedef  int /*<<< orphan*/  VOID ;
typedef  int UCHAR ;
typedef  scalar_t__ PUCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  READ_PORT_UCHAR (scalar_t__) ; 
 int /*<<< orphan*/  WRITE_PORT_UCHAR (scalar_t__,int) ; 

__attribute__((used)) static
VOID
InitializeSerialPort(PUCHAR Port,
                     UCHAR LineControl)
{
    WRITE_PORT_UCHAR(Port + 3, 0x80);  /* set DLAB on   */
    WRITE_PORT_UCHAR(Port,     0x60);  /* speed LO byte */
    WRITE_PORT_UCHAR(Port + 1, 0);     /* speed HI byte */
    WRITE_PORT_UCHAR(Port + 3, LineControl);
    WRITE_PORT_UCHAR(Port + 1, 0);     /* set comm and DLAB to 0 */
    WRITE_PORT_UCHAR(Port + 4, 0x09);  /* DR int enable */
    READ_PORT_UCHAR(Port + 5);  /* clear error bits */
}