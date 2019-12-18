#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  mmgr; int /*<<< orphan*/  error; } ;
typedef  int /*<<< orphan*/  HPDF_STATUS ;
typedef  scalar_t__ HPDF_InfoType ;
typedef  int /*<<< orphan*/  HPDF_Encoder ;
typedef  TYPE_1__* HPDF_Dict ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_Dict_Add (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_Dict_AddName (TYPE_1__*,char const*,char const*) ; 
 scalar_t__ HPDF_INFO_MOD_DATE ; 
 scalar_t__ HPDF_INFO_TRAPPED ; 
 int /*<<< orphan*/  HPDF_INVALID_PARAMETER ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_SetError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_String_New (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 char* InfoTypeToName (scalar_t__) ; 

HPDF_STATUS
HPDF_Info_SetInfoAttr (HPDF_Dict        info,
                       HPDF_InfoType    type,
                       const char  *value,
                       HPDF_Encoder     encoder)
{
    const char* name = InfoTypeToName (type);

    HPDF_PTRACE((" HPDF_Info_SetInfoAttr\n"));

    if (type <= HPDF_INFO_MOD_DATE)
        return HPDF_SetError (info->error, HPDF_INVALID_PARAMETER, 0);

    if (type == HPDF_INFO_TRAPPED)
        return HPDF_Dict_AddName(info, name, value);

    return HPDF_Dict_Add (info, name, HPDF_String_New (info->mmgr, value,
            encoder));
}