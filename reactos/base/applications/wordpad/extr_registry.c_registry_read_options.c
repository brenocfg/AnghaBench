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
typedef  int /*<<< orphan*/ * HKEY ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_options ; 
 int /*<<< orphan*/  key_settings ; 
 scalar_t__ registry_get_handle (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  registry_read_pagemargins (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  registry_read_previewpages (int /*<<< orphan*/ *) ; 

void registry_read_options(void)
{
    HKEY hKey;

    if(registry_get_handle(&hKey, 0, key_options) != ERROR_SUCCESS)
        registry_read_pagemargins(NULL);
    else
    {
        registry_read_pagemargins(hKey);
        RegCloseKey(hKey);
    }

    if(registry_get_handle(&hKey, 0, key_settings) != ERROR_SUCCESS) {
        registry_read_previewpages(NULL);
    } else {
        registry_read_previewpages(hKey);
        RegCloseKey(hKey);
    }
}