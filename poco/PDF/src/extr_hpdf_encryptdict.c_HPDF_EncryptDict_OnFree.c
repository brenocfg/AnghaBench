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
struct TYPE_3__ {int /*<<< orphan*/  mmgr; int /*<<< orphan*/  attr; } ;
typedef  scalar_t__ HPDF_Encrypt ;
typedef  TYPE_1__* HPDF_Dict ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_FreeMem (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 

void
HPDF_EncryptDict_OnFree  (HPDF_Dict  obj)
{
    HPDF_Encrypt attr = (HPDF_Encrypt)obj->attr;

    HPDF_PTRACE((" HPDF_EncryptDict_OnFree\n"));

    if (attr)
        HPDF_FreeMem (obj->mmgr, attr);
}