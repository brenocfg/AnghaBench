#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  stream; } ;
typedef  int /*<<< orphan*/  HPDF_Xref ;
typedef  scalar_t__ HPDF_STATUS ;
typedef  TYPE_1__* HPDF_Number ;
typedef  int /*<<< orphan*/  HPDF_MMgr ;
typedef  TYPE_1__* HPDF_Dict ;

/* Variables and functions */
 scalar_t__ HPDF_Dict_Add (TYPE_1__*,char*,TYPE_1__*) ; 
 TYPE_1__* HPDF_Dict_New (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_MemStream_New (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* HPDF_Number_New (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_OK ; 
 int /*<<< orphan*/  HPDF_STREAM_BUF_SIZ ; 
 scalar_t__ HPDF_Xref_Add (int /*<<< orphan*/ ,TYPE_1__*) ; 

HPDF_Dict
HPDF_DictStream_New  (HPDF_MMgr  mmgr,
                      HPDF_Xref  xref)
{
    HPDF_Dict  obj;
    HPDF_Number length;
    HPDF_STATUS ret = 0;

    obj = HPDF_Dict_New (mmgr);
    if (!obj)
        return NULL;

    /* only stream object is added to xref automatically */
    ret += HPDF_Xref_Add (xref, obj);
    if (ret != HPDF_OK)
        return NULL;

    length = HPDF_Number_New (mmgr, 0);
    if (!length)
        return NULL;

    ret = HPDF_Xref_Add (xref, length);
    if (ret != HPDF_OK)
        return NULL;

    ret = HPDF_Dict_Add (obj, "Length", length);
    if (ret != HPDF_OK)
        return NULL;

    obj->stream = HPDF_MemStream_New (mmgr, HPDF_STREAM_BUF_SIZ);
    if (!obj->stream)
        return NULL;

    return obj;
}