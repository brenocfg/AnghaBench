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
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ ISMARU (unsigned char) ; 
 scalar_t__ ISNIGORI (unsigned char) ; 
 scalar_t__ TRUE ; 

__attribute__((used)) static int han2zen(unsigned char *p1, unsigned char *p2)
{
    BOOL maru = FALSE;
    BOOL nigori = FALSE;
    static const unsigned char char1[] = {129,129,129,129,129,131,131,131,131,
        131,131,131,131,131,131,129,131,131,131,131,131,131,131,131,131,131,
        131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,
        131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,131,
        131,129,129 };
    static const unsigned char char2[] = {66,117,118,65,69,146,64,66,68,70,
        72,131,133,135,98,91,65,67,69,71,73,74,76,78,80,82,84,86,88,90,92,94,
        96,99,101,103,105,106,107,108,109,110,113,116,119,122,125,126,128,
        129,130,132,134,136,137,138,139,140,141,143,147,74,75};

    if (( *p2 == 222) && ((ISNIGORI(*p1) || (*p1 == 179))))
            nigori = TRUE;
    else if ((*p2 == 223) && (ISMARU(*p1)))
            maru = TRUE;

    if (*p1 >= 161 && *p1 <= 223)
    {
        unsigned char index = *p1 - 161;
        *p1 = char1[index];
        *p2 = char2[index];
    }

    if (maru || nigori)
    {
        if (nigori)
        {
            if (((*p2 >= 74) && (*p2 <= 103)) || ((*p2 >= 110) && (*p2 <= 122)))
                (*p2)++;
            else if ((*p1 == 131) && (*p2 == 69))
                *p2 = 148;
        }
        else if ((maru) && ((*p2 >= 110) && (*p2 <= 122)))
            *p2+= 2;

        return 1;
    }

    return 0;
}