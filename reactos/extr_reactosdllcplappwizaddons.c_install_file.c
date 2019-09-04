#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  enum install_res { ____Placeholder_install_res } install_res ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ ULONG ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,scalar_t__) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int INSTALL_FAILED ; 
 int INSTALL_OK ; 
 scalar_t__ MsiInstallProductW (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum install_res install_file(const WCHAR *file_name)
{
    ULONG res;

    res = MsiInstallProductW(file_name, NULL);
    if(res != ERROR_SUCCESS) {
        ERR("MsiInstallProduct failed: %u\n", res);
        return INSTALL_FAILED;
    }

    return INSTALL_OK;
}