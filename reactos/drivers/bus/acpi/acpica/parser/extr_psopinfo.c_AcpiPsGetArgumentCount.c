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
typedef  int /*<<< orphan*/  UINT8 ;
typedef  size_t UINT32 ;

/* Variables and functions */
 size_t AML_TYPE_EXEC_6A_0T_1R ; 
 int /*<<< orphan*/ * AcpiGbl_ArgumentCount ; 

UINT8
AcpiPsGetArgumentCount (
    UINT32                  OpType)
{

    if (OpType <= AML_TYPE_EXEC_6A_0T_1R)
    {
        return (AcpiGbl_ArgumentCount[OpType]);
    }

    return (0);
}