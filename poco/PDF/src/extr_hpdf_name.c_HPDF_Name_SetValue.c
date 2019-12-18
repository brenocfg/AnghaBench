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
struct TYPE_3__ {scalar_t__ value; int /*<<< orphan*/  error; } ;
typedef  int /*<<< orphan*/  HPDF_STATUS ;
typedef  TYPE_1__* HPDF_Name ;

/* Variables and functions */
 scalar_t__ HPDF_LIMIT_MAX_NAME_LEN ; 
 int /*<<< orphan*/  HPDF_NAME_INVALID_VALUE ; 
 int /*<<< orphan*/  HPDF_NAME_OUT_OF_RANGE ; 
 int /*<<< orphan*/  HPDF_OK ; 
 int /*<<< orphan*/  HPDF_SetError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_StrCpy (scalar_t__,char const*,scalar_t__) ; 
 scalar_t__ HPDF_StrLen (char const*,scalar_t__) ; 

HPDF_STATUS
HPDF_Name_SetValue  (HPDF_Name        obj,
                     const char  *value)
{
    if (!value || value[0] == 0)
        return HPDF_SetError (obj->error, HPDF_NAME_INVALID_VALUE, 0);

    if (HPDF_StrLen (value, HPDF_LIMIT_MAX_NAME_LEN + 1) >
            HPDF_LIMIT_MAX_NAME_LEN)
        return HPDF_SetError (obj->error, HPDF_NAME_OUT_OF_RANGE, 0);

    HPDF_StrCpy (obj->value, value, obj->value + HPDF_LIMIT_MAX_NAME_LEN);

    return HPDF_OK;
}