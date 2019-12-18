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
typedef  int DWORD ;
typedef  char BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL text_xml_filter(const BYTE *b, DWORD size)
{
    if(size < 7)
        return FALSE;

    if(b[0] == '<' && b[1] == '?'
            && (b[2] == 'x' || b[2] == 'X')
            && (b[3] == 'm' || b[3] == 'M')
            && (b[4] == 'l' || b[4] == 'L')
            && b[5] == ' ') return TRUE;

    return FALSE;
}