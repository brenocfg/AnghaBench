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
struct TYPE_3__ {scalar_t__ len; int /*<<< orphan*/  value; } ;
typedef  int /*<<< orphan*/  HPDF_Stream ;
typedef  int /*<<< orphan*/  HPDF_STATUS ;
typedef  scalar_t__ HPDF_Encrypt ;
typedef  TYPE_1__* HPDF_Binary ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_Encrypt_Reset (scalar_t__) ; 
 int /*<<< orphan*/  HPDF_OK ; 
 int /*<<< orphan*/  HPDF_Stream_WriteBinary (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  HPDF_Stream_WriteChar (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  HPDF_Stream_WriteStr (int /*<<< orphan*/ ,char*) ; 

HPDF_STATUS
HPDF_Binary_Write  (HPDF_Binary   obj,
                    HPDF_Stream   stream,
                    HPDF_Encrypt  e)
{
    HPDF_STATUS ret;

    if (obj->len == 0)
        return HPDF_Stream_WriteStr (stream, "<>");

    if ((ret = HPDF_Stream_WriteChar (stream, '<')) != HPDF_OK)
        return ret;

    if (e)
        HPDF_Encrypt_Reset (e);

    if ((ret = HPDF_Stream_WriteBinary (stream, obj->value, obj->len, e)) !=
                    HPDF_OK)
        return ret;

    return HPDF_Stream_WriteChar (stream, '>');
}