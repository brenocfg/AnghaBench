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
typedef  int /*<<< orphan*/  FILE ;
typedef  int BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int fread (int*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  processRegLinesA (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  processRegLinesW (int /*<<< orphan*/ *) ; 

BOOL import_registry_file(FILE* reg_file)
{
    if (reg_file)
    {
        BYTE s[2];
        if (fread( s, 2, 1, reg_file) == 1)
        {
            if (s[0] == 0xff && s[1] == 0xfe)
            {
                processRegLinesW(reg_file);
            } else
            {
                processRegLinesA(reg_file, (char*)s);
            }
        }
        return TRUE;
    }
    return FALSE;
}