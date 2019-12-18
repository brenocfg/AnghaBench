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
typedef  scalar_t__ HPDF_UINT ;
typedef  scalar_t__ HPDF_Outline ;

/* Variables and functions */
 scalar_t__ HPDF_Outline_GetFirst (scalar_t__) ; 
 scalar_t__ HPDF_Outline_GetNext (scalar_t__) ; 
 scalar_t__ HPDF_Outline_GetOpened (scalar_t__) ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 

__attribute__((used)) static HPDF_UINT
CountChild (HPDF_Outline  outline)
{
    HPDF_Outline  child = HPDF_Outline_GetFirst (outline);
    HPDF_UINT count = 0;

    HPDF_PTRACE((" CountChild\n"));

    while (child) {
        count++;

        if (HPDF_Outline_GetOpened (child))
            count += CountChild (child);

        child = HPDF_Outline_GetNext (child);
    }

    return count;
}