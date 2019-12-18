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
typedef  int /*<<< orphan*/  HPDF_Outline ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_Dict_GetItem (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_OCLASS_DICT ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 

HPDF_Outline
HPDF_Outline_GetLast  (HPDF_Outline outline)
{
    HPDF_PTRACE((" HPDF_Outline_GetLast\n"));

    return (HPDF_Outline)HPDF_Dict_GetItem (outline, "Last", HPDF_OCLASS_DICT);
}