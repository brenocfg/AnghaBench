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
 int /*<<< orphan*/  rev ; 
 scalar_t__ sortcol ; 
 int strcmp (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

int cmpr(const void *a, const void *b)
{
    char *A, *B;

    A = *(char **) a;
    B = *(char **) b;

    if (sortcol > 0)
    {
        if (strlen(A) > sortcol)
        {
            A += sortcol;
        }
        else
        {
            A = "";
        }
        if (strlen(B) > sortcol)
        {
            B += sortcol;
        }
        else
        {
            B = "";
        }
    }

    if (!rev)
    {
        return strcmp(A, B);
    }
    else
    {
        return strcmp(B, A);
    }
}