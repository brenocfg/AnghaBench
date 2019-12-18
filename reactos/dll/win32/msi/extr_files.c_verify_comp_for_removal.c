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
typedef  scalar_t__ UINT ;
struct TYPE_3__ {int Action; int Attributes; } ;
typedef  TYPE_1__ MSICOMPONENT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
#define  INSTALLSTATE_ABSENT 130 
#define  INSTALLSTATE_LOCAL 129 
#define  INSTALLSTATE_SOURCE 128 
 int /*<<< orphan*/  TRUE ; 
 int msidbComponentAttributesSourceOnly ; 
 scalar_t__ msidbRemoveFileInstallModeOnBoth ; 
 scalar_t__ msidbRemoveFileInstallModeOnInstall ; 
 scalar_t__ msidbRemoveFileInstallModeOnRemove ; 

__attribute__((used)) static BOOL verify_comp_for_removal(MSICOMPONENT *comp, UINT install_mode)
{
    /* special case */
    if (comp->Action != INSTALLSTATE_SOURCE &&
        comp->Attributes & msidbComponentAttributesSourceOnly &&
        (install_mode == msidbRemoveFileInstallModeOnRemove ||
         install_mode == msidbRemoveFileInstallModeOnBoth)) return TRUE;

    switch (comp->Action)
    {
    case INSTALLSTATE_LOCAL:
    case INSTALLSTATE_SOURCE:
        if (install_mode == msidbRemoveFileInstallModeOnInstall ||
            install_mode == msidbRemoveFileInstallModeOnBoth) return TRUE;
        break;
    case INSTALLSTATE_ABSENT:
        if (install_mode == msidbRemoveFileInstallModeOnRemove ||
            install_mode == msidbRemoveFileInstallModeOnBoth) return TRUE;
        break;
    default: break;
    }
    return FALSE;
}