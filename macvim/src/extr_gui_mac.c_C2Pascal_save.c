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
typedef  int char_u ;

/* Variables and functions */
 int STRLEN (int*) ; 
 int* alloc (int) ; 
 int /*<<< orphan*/  mch_memmove (int*,int*,int) ; 

char_u *
C2Pascal_save(char_u *Cstring)
{
    char_u  *PascalString;
    int	    len;

    if (Cstring == NULL)
	return NULL;

    len = STRLEN(Cstring);

    if (len > 255) /* Truncate if necessary */
	len = 255;

    PascalString = alloc(len + 1);
    if (PascalString != NULL)
    {
	mch_memmove(PascalString + 1, Cstring, len);
	PascalString[0] = len;
    }

    return PascalString;
}