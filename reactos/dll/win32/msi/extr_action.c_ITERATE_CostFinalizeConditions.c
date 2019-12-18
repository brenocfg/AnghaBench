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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {int Level; } ;
typedef  int /*<<< orphan*/  MSIRECORD ;
typedef  int /*<<< orphan*/  MSIPACKAGE ;
typedef  TYPE_1__ MSIFEATURE ;
typedef  int /*<<< orphan*/ * LPVOID ;
typedef  int /*<<< orphan*/  LPCWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 scalar_t__ MSICONDITION_TRUE ; 
 scalar_t__ MSI_EvaluateConditionW (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MSI_RecordGetInteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  MSI_RecordGetString (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 TYPE_1__* msi_get_loaded_feature (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static UINT ITERATE_CostFinalizeConditions(MSIRECORD *row, LPVOID param)
{
    MSIPACKAGE *package = param;
    LPCWSTR name;
    MSIFEATURE *feature;

    name = MSI_RecordGetString( row, 1 );

    feature = msi_get_loaded_feature( package, name );
    if (!feature)
        ERR("FAILED to find loaded feature %s\n",debugstr_w(name));
    else
    {
        LPCWSTR Condition;
        Condition = MSI_RecordGetString(row,3);

        if (MSI_EvaluateConditionW(package,Condition) == MSICONDITION_TRUE)
        {
            int level = MSI_RecordGetInteger(row,2);
            TRACE("Resetting feature %s to level %i\n", debugstr_w(name), level);
            feature->Level = level;
        }
    }
    return ERROR_SUCCESS;
}