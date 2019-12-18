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
typedef  int /*<<< orphan*/  buffer ;
typedef  scalar_t__ HKEY ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  RegCloseKey (scalar_t__) ; 
 scalar_t__ RegOpenKeyA (scalar_t__,char const*,scalar_t__*) ; 
 int /*<<< orphan*/  TRACE (char*,char const*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  get_app_key (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  get_config_key (scalar_t__,scalar_t__,char const*,char*,int) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

BOOL device_disabled_registry(const char* name)
{
    static const char disabled_str[] = "disabled";
    static const char joystick_key[] = "Joysticks";
    char buffer[MAX_PATH];
    HKEY hkey, appkey, temp;
    BOOL do_disable = FALSE;

    get_app_key(&hkey, &appkey);

    /* Joystick settings are in the 'joysticks' subkey */
    if (appkey)
    {
        if (RegOpenKeyA(appkey, joystick_key, &temp)) temp = 0;
        RegCloseKey(appkey);
        appkey = temp;
    }
    if (hkey)
    {
        if (RegOpenKeyA(hkey, joystick_key, &temp)) temp = 0;
        RegCloseKey(hkey);
        hkey = temp;
    }

    /* Look for the "controllername"="disabled" key */
    if (!get_config_key(hkey, appkey, name, buffer, sizeof(buffer)))
        if (!strcmp(disabled_str, buffer))
        {
            TRACE("Disabling joystick '%s' based on registry key.\n", name);
            do_disable = TRUE;
        }

    if (appkey) RegCloseKey(appkey);
    if (hkey)   RegCloseKey(hkey);

    return do_disable;
}