#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  threadDefault; } ;
typedef  TYPE_1__ InputContextData ;
typedef  int /*<<< orphan*/  HIMC ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 TYPE_1__* get_imc_data (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL IMM_IsDefaultContext(HIMC imc)
{
    InputContextData *data = get_imc_data(imc);

    if (!data)
        return FALSE;

    return data->threadDefault;
}