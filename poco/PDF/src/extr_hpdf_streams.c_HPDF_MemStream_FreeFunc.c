#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  buf; } ;
struct TYPE_6__ {int /*<<< orphan*/ * attr; int /*<<< orphan*/  mmgr; } ;
typedef  TYPE_1__* HPDF_Stream ;
typedef  TYPE_2__* HPDF_MemStreamAttr ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_FreeMem (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  HPDF_List_Free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_MemStream_FreeData (TYPE_1__*) ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 

void
HPDF_MemStream_FreeFunc  (HPDF_Stream  stream)
{
    HPDF_MemStreamAttr attr;

    HPDF_PTRACE((" HPDF_MemStream_FreeFunc\n"));

    attr = (HPDF_MemStreamAttr)stream->attr;
    HPDF_MemStream_FreeData (stream);
    HPDF_List_Free (attr->buf);
    HPDF_FreeMem (stream->mmgr, attr);
    stream->attr = NULL;
}