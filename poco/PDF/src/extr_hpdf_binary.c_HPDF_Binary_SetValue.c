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
typedef  int /*<<< orphan*/  HPDF_STATUS ;
typedef  TYPE_1__* HPDF_Binary ;
typedef  int /*<<< orphan*/  HPDF_BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_BINARY_LENGTH_ERR ; 
 int /*<<< orphan*/  HPDF_Error_GetCode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_FreeMem (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ HPDF_GetMem (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ HPDF_LIMIT_MAX_STRING_LEN ; 
 int /*<<< orphan*/  HPDF_MemCpy (scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  HPDF_OK ; 
 int /*<<< orphan*/  HPDF_SetError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

HPDF_STATUS
HPDF_Binary_SetValue  (HPDF_Binary  obj,
                       HPDF_BYTE    *value,
                       HPDF_UINT    len)
{
    if (len > HPDF_LIMIT_MAX_STRING_LEN)
        return HPDF_SetError (obj->error, HPDF_BINARY_LENGTH_ERR, 0);

    if (obj->value) {
        HPDF_FreeMem (obj->mmgr, obj->value);
        obj->len = 0;
    }

    obj->value = HPDF_GetMem (obj->mmgr, len);
    if (!obj->value)
        return HPDF_Error_GetCode (obj->error);

    HPDF_MemCpy (obj->value, value, len);
    obj->len = len;

    return HPDF_OK;
}