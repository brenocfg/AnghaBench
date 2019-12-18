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
struct TYPE_5__ {int /*<<< orphan*/  install_sec; int /*<<< orphan*/  hinf; } ;
typedef  scalar_t__ HRESULT ;
typedef  TYPE_1__ ADVInfo ;

/* Variables and functions */
 int /*<<< orphan*/  DelDirs ; 
 int /*<<< orphan*/  OleInitialize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OleUninitialize () ; 
 int /*<<< orphan*/  PerUserInstall ; 
 int /*<<< orphan*/  RegisterOCXs ; 
 int /*<<< orphan*/  RunPostSetupCommands ; 
 int /*<<< orphan*/  RunPreSetupCommands ; 
 scalar_t__ S_OK ; 
 scalar_t__ check_admin_rights (TYPE_1__*) ; 
 int /*<<< orphan*/  del_dirs_callback ; 
 scalar_t__ iterate_section_fields (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  per_user_install_callback ; 
 int /*<<< orphan*/  register_ocxs_callback ; 
 int /*<<< orphan*/  run_setup_commands_callback ; 

__attribute__((used)) static HRESULT adv_install(ADVInfo *info)
{
    HRESULT hr;

    hr = check_admin_rights(info);
    if (hr != S_OK)
        return hr;

    hr = iterate_section_fields(info->hinf, info->install_sec, RunPreSetupCommands,
                                run_setup_commands_callback, info);
    if (hr != S_OK)
        return hr;

    OleInitialize(NULL);
    hr = iterate_section_fields(info->hinf, info->install_sec,
                                RegisterOCXs, register_ocxs_callback, NULL);
    OleUninitialize();
    if (hr != S_OK)
        return hr;

    hr = iterate_section_fields(info->hinf, info->install_sec,
                                PerUserInstall, per_user_install_callback, info);
    if (hr != S_OK)
        return hr;

    hr = iterate_section_fields(info->hinf, info->install_sec, RunPostSetupCommands,
                                run_setup_commands_callback, info);
    if (hr != S_OK)
        return hr;

    hr = iterate_section_fields(info->hinf, info->install_sec,
                                DelDirs, del_dirs_callback, info);
    if (hr != S_OK)
        return hr;

    return hr;
}