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
typedef  scalar_t__ HKEY ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ DS_HW_ACCEL_BASIC ; 
 scalar_t__ DS_HW_ACCEL_EMULATION ; 
 scalar_t__ DS_HW_ACCEL_FULL ; 
 scalar_t__ DS_HW_ACCEL_STANDARD ; 
 int GetModuleFileNameA (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ HKEY_CURRENT_USER ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  RegCloseKey (scalar_t__) ; 
 scalar_t__ RegOpenKeyA (scalar_t__,char*,scalar_t__*) ; 
 int /*<<< orphan*/  TRACE (char*,char*) ; 
 void* atoi (char*) ; 
 char* ds_default_bits_per_sample ; 
 void* ds_default_capture ; 
 char* ds_default_playback ; 
 char* ds_default_sample_rate ; 
 char* ds_emuldriver ; 
 char* ds_hel_buflen ; 
 scalar_t__ ds_hw_accel ; 
 char* ds_snd_queue_max ; 
 char* ds_snd_queue_min ; 
 char* ds_snd_shadow_maxsize ; 
 int /*<<< orphan*/  get_config_key (scalar_t__,scalar_t__,char*,char*,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strrchr (char*,char) ; 

void setup_dsound_options(void)
{
    char buffer[MAX_PATH+16];
    HKEY hkey, appkey = 0;
    DWORD len;

    buffer[MAX_PATH]='\0';

    /* @@ Wine registry key: HKCU\Software\Wine\DirectSound */
    if (RegOpenKeyA( HKEY_CURRENT_USER, "Software\\Wine\\DirectSound", &hkey )) hkey = 0;

    len = GetModuleFileNameA( 0, buffer, MAX_PATH );
    if (len && len < MAX_PATH)
    {
        HKEY tmpkey;
        /* @@ Wine registry key: HKCU\Software\Wine\AppDefaults\app.exe\DirectSound */
        if (!RegOpenKeyA( HKEY_CURRENT_USER, "Software\\Wine\\AppDefaults", &tmpkey ))
        {
            char *p, *appname = buffer;
            if ((p = strrchr( appname, '/' ))) appname = p + 1;
            if ((p = strrchr( appname, '\\' ))) appname = p + 1;
            strcat( appname, "\\DirectSound" );
            TRACE("appname = [%s]\n", appname);
            if (RegOpenKeyA( tmpkey, appname, &appkey )) appkey = 0;
            RegCloseKey( tmpkey );
        }
    }

    /* get options */

    if (!get_config_key( hkey, appkey, "EmulDriver", buffer, MAX_PATH ))
        ds_emuldriver = strcmp(buffer, "N");

    if (!get_config_key( hkey, appkey, "HelBuflen", buffer, MAX_PATH ))
        ds_hel_buflen = atoi(buffer);

    if (!get_config_key( hkey, appkey, "SndQueueMax", buffer, MAX_PATH ))
        ds_snd_queue_max = atoi(buffer);

    if (!get_config_key( hkey, appkey, "SndQueueMin", buffer, MAX_PATH ))
        ds_snd_queue_min = atoi(buffer);

    if (!get_config_key( hkey, appkey, "HardwareAcceleration", buffer, MAX_PATH )) {
	if (strcmp(buffer, "Full") == 0)
	    ds_hw_accel = DS_HW_ACCEL_FULL;
	else if (strcmp(buffer, "Standard") == 0)
	    ds_hw_accel = DS_HW_ACCEL_STANDARD;
	else if (strcmp(buffer, "Basic") == 0)
	    ds_hw_accel = DS_HW_ACCEL_BASIC;
	else if (strcmp(buffer, "Emulation") == 0)
	    ds_hw_accel = DS_HW_ACCEL_EMULATION;
    }

    if (!get_config_key( hkey, appkey, "DefaultPlayback", buffer, MAX_PATH ))
        ds_default_playback = atoi(buffer);

    if (!get_config_key( hkey, appkey, "MaxShadowSize", buffer, MAX_PATH ))
        ds_snd_shadow_maxsize = atoi(buffer);

    if (!get_config_key( hkey, appkey, "DefaultCapture", buffer, MAX_PATH ))
        ds_default_capture = atoi(buffer);

    if (!get_config_key( hkey, appkey, "DefaultSampleRate", buffer, MAX_PATH ))
        ds_default_sample_rate = atoi(buffer);

    if (!get_config_key( hkey, appkey, "DefaultBitsPerSample", buffer, MAX_PATH ))
        ds_default_bits_per_sample = atoi(buffer);

    if (appkey) RegCloseKey( appkey );
    if (hkey) RegCloseKey( hkey );

    TRACE("ds_emuldriver = %d\n", ds_emuldriver);
    TRACE("ds_hel_buflen = %d\n", ds_hel_buflen);
    TRACE("ds_snd_queue_max = %d\n", ds_snd_queue_max);
    TRACE("ds_snd_queue_min = %d\n", ds_snd_queue_min);
    TRACE("ds_hw_accel = %s\n",
        ds_hw_accel==DS_HW_ACCEL_FULL ? "Full" :
        ds_hw_accel==DS_HW_ACCEL_STANDARD ? "Standard" :
        ds_hw_accel==DS_HW_ACCEL_BASIC ? "Basic" :
        ds_hw_accel==DS_HW_ACCEL_EMULATION ? "Emulation" :
        "Unknown");
    TRACE("ds_default_playback = %d\n", ds_default_playback);
    TRACE("ds_default_capture = %d\n", ds_default_playback);
    TRACE("ds_default_sample_rate = %d\n", ds_default_sample_rate);
    TRACE("ds_default_bits_per_sample = %d\n", ds_default_bits_per_sample);
    TRACE("ds_snd_shadow_maxsize = %d\n", ds_snd_shadow_maxsize);
}