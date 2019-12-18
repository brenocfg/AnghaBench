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
struct TYPE_3__ {scalar_t__ value; } ;
typedef  int /*<<< orphan*/  HPDF_Stream ;
typedef  int /*<<< orphan*/  HPDF_STATUS ;
typedef  TYPE_1__* HPDF_Boolean ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_Stream_WriteStr (int /*<<< orphan*/ ,char*) ; 

HPDF_STATUS
HPDF_Boolean_Write  (HPDF_Boolean  obj,
                     HPDF_Stream   stream)
{
    HPDF_STATUS ret;

    if (obj->value)
        ret = HPDF_Stream_WriteStr (stream, "true");
    else
        ret = HPDF_Stream_WriteStr (stream, "false");

    return ret;
}