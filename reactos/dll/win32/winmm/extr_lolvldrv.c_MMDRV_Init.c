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
typedef  int /*<<< orphan*/  driver_buffer ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 scalar_t__ LoadRegistryMMEDrivers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMDRV_Install (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NT_MME_DRIVERS32_KEY ; 
 int /*<<< orphan*/  NT_MME_DRIVERS_KEY ; 
 int /*<<< orphan*/  RegOpenKeyA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 char* WINE_DEFAULT_WINMM_DRIVER ; 
 char* WINE_DEFAULT_WINMM_MAPPER ; 
 char* WINE_DEFAULT_WINMM_MIDI ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

BOOL	MMDRV_Init(void)
{
/* Redundant code, keeping this for reference only (for now) */
#if 0
    HKEY	hKey;
    char	driver_buffer[256];
    char	mapper_buffer[256];
    char	midi_buffer[256];
    char*	p;
    DWORD	type, size;
    BOOL	ret = FALSE;
    TRACE("()\n");

    strcpy(driver_buffer, WINE_DEFAULT_WINMM_DRIVER);
    strcpy(mapper_buffer, WINE_DEFAULT_WINMM_MAPPER);
    strcpy(midi_buffer, WINE_DEFAULT_WINMM_MIDI);

    /* @@ Wine registry key: HKCU\Software\Wine\Drivers */
    if (!RegOpenKeyA(HKEY_CURRENT_USER, "Software\\Wine\\Drivers", &hKey))
    {
        size = sizeof(driver_buffer);
        if (RegQueryValueExA(hKey, "Audio", 0, &type, (LPVOID)driver_buffer, &size))
            strcpy(driver_buffer, WINE_DEFAULT_WINMM_DRIVER);
    }

    p = driver_buffer;
    while (p)
    {
        char filename[sizeof(driver_buffer)+10];
        char *next = strchr(p, ',');
        if (next) *next++ = 0;
        sprintf( filename, "wine%s.drv", p );
        if ((ret = MMDRV_Install( filename, filename, FALSE ))) break;
        p = next;
    }

    ret |= MMDRV_Install("beepmidi.dll", "beepmidi.dll", FALSE);

    ret |= MMDRV_Install("wavemapper", WINE_DEFAULT_WINMM_MAPPER, TRUE);
    ret |= MMDRV_Install("midimapper", WINE_DEFAULT_WINMM_MIDI, TRUE);
    return ret;
#else
    INT driver_count = 0;

    driver_count += LoadRegistryMMEDrivers(NT_MME_DRIVERS_KEY);
    driver_count += LoadRegistryMMEDrivers(NT_MME_DRIVERS32_KEY);

    /* Explorer doesn't like us failing */
    return TRUE;
//    return ( driver_count > 0 );
#endif
}