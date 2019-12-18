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
struct TYPE_3__ {scalar_t__ len; scalar_t__ value; int /*<<< orphan*/  error; int /*<<< orphan*/  mmgr; } ;
typedef  scalar_t__ HPDF_UINT ;
typedef  TYPE_1__* HPDF_String ;
typedef  int /*<<< orphan*/  HPDF_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_Error_GetCode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_FreeMem (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ HPDF_GetMem (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ HPDF_LIMIT_MAX_STRING_LEN ; 
 int /*<<< orphan*/  HPDF_OK ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_STRING_OUT_OF_RANGE ; 
 int /*<<< orphan*/  HPDF_SetError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_StrCpy (char*,char const*,char*) ; 
 scalar_t__ HPDF_StrLen (char const*,scalar_t__) ; 

HPDF_STATUS
HPDF_String_SetValue  (HPDF_String      obj,
                       const char  *value)
{
    HPDF_UINT len;
    HPDF_STATUS ret = HPDF_OK;

    HPDF_PTRACE((" HPDF_String_SetValue\n"));

    if (obj->value) {
        HPDF_FreeMem (obj->mmgr, obj->value);
        obj->len = 0;
    }

    len = HPDF_StrLen(value, HPDF_LIMIT_MAX_STRING_LEN + 1);

    if (len > HPDF_LIMIT_MAX_STRING_LEN)
        return HPDF_SetError (obj->error, HPDF_STRING_OUT_OF_RANGE, 0);

    obj->value = HPDF_GetMem (obj->mmgr, len + 1);
    if (!obj->value)
        return HPDF_Error_GetCode (obj->error);

    HPDF_StrCpy ((char *)obj->value, value, (char *)obj->value + len);
    obj->len = len;

    return ret;
}