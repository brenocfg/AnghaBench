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
 int FALSE ; 
 int TRUE ; 

__attribute__((used)) static int
xsltIsDigitZero(unsigned int ch)
{
    /*
     * Reference: ftp://ftp.unicode.org/Public/UNIDATA/UnicodeData.txt
     */
    switch (ch) {
    case 0x0030: case 0x0660: case 0x06F0: case 0x0966:
    case 0x09E6: case 0x0A66: case 0x0AE6: case 0x0B66:
    case 0x0C66: case 0x0CE6: case 0x0D66: case 0x0E50:
    case 0x0E60: case 0x0F20: case 0x1040: case 0x17E0:
    case 0x1810: case 0xFF10:
	return TRUE;
    default:
	return FALSE;
    }
}