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
typedef  int UCHAR ;

/* Variables and functions */

__attribute__((used)) static
UCHAR
CharToHex(WCHAR Char)
{
    if ((Char >= L'0') && (Char <= L'9'))
        return Char - L'0';

    if ((Char >= L'a') && (Char <= L'f'))
        return Char - L'a' + 10;

    if ((Char >= L'A') && (Char <= L'F'))
        return Char - L'A' + 10;

    return 0;
}