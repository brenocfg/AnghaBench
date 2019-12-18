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
typedef  char WCHAR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (char*,char*,int) ; 

__attribute__((used)) static void strip_quotes(WCHAR *buffer, DWORD *size)
{
    if (buffer[0] == '\'' && (*size > 1) && buffer[*size-2]=='\'')
    {
        *size -= 2;
        buffer[*size] = 0x00;
        memmove(buffer, buffer + 1, *size * sizeof(WCHAR));
    }
}