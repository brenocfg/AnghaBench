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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  DefaultContainerData ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
#define  COOKIE_CACHE_ENTRY 133 
 int /*<<< orphan*/  CP_ACP ; 
#define  CSIDL_COOKIES 132 
#define  CSIDL_HISTORY 131 
#define  CSIDL_INTERNET_CACHE 130 
 int /*<<< orphan*/  ERR (char*,...) ; 
 scalar_t__ ERROR_ENVVAR_NOT_FOUND ; 
 scalar_t__ GetEnvironmentVariableW (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ GetLastError () ; 
 int GetShortPathNameW (char*,char*,int) ; 
 int MAX_PATH ; 
#define  NORMAL_CACHE_ENTRY 129 
 int /*<<< orphan*/  SHGetSpecialFolderPathW (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
#define  URLHISTORY_CACHE_ENTRY 128 
 int /*<<< orphan*/  WC_NO_BEST_FIT_CHARS ; 
 int /*<<< orphan*/  WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  bDefaultContainersAdded ; 
 int /*<<< orphan*/  cache_containers_add (char const*,char*,int,char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  strcpyW (char*,char*) ; 
 int strlenW (char*) ; 

__attribute__((used)) static void cache_containers_init(void)
{
    static const WCHAR UrlSuffix[] = {'C','o','n','t','e','n','t','.','I','E','5',0};
    static const WCHAR HistorySuffix[] = {'H','i','s','t','o','r','y','.','I','E','5',0};
    static const WCHAR CookieSuffix[] = {0};
    /* ReactOS r50916 */
    static const WCHAR UserProfile[] = {'U','S','E','R','P','R','O','F','I','L','E',0};
    static const struct
    {
        int nFolder; /* CSIDL_* constant */
        const WCHAR *shpath_suffix; /* suffix on path returned by SHGetSpecialFolderPath */
        const char *cache_prefix; /* prefix used to reference the container */
        DWORD default_entry_type;
    } DefaultContainerData[] = 
    {
        { CSIDL_INTERNET_CACHE, UrlSuffix, "", NORMAL_CACHE_ENTRY },
        { CSIDL_HISTORY, HistorySuffix, "Visited:", URLHISTORY_CACHE_ENTRY },
        { CSIDL_COOKIES, CookieSuffix, "Cookie:", COOKIE_CACHE_ENTRY },
    };
    DWORD i;

    /* ReactOS r50916 */
    if (GetEnvironmentVariableW(UserProfile, NULL, 0) == 0 && GetLastError() == ERROR_ENVVAR_NOT_FOUND)
    {
        ERR("Environment variable 'USERPROFILE' does not exist!\n");
        return;
    }

    for (i = 0; i < sizeof(DefaultContainerData) / sizeof(DefaultContainerData[0]); i++)
    {
        WCHAR wszCachePath[MAX_PATH];
        WCHAR wszMutexName[MAX_PATH];
        int path_len, suffix_len;
        BOOL def_char;

        if (!SHGetSpecialFolderPathW(NULL, wszCachePath, DefaultContainerData[i].nFolder, TRUE))
        {
            ERR("Couldn't get path for default container %u\n", i);
            continue;
        }
        path_len = strlenW(wszCachePath);
        suffix_len = strlenW(DefaultContainerData[i].shpath_suffix);

        if (path_len + suffix_len + 2 > MAX_PATH)
        {
            ERR("Path too long\n");
            continue;
        }

        wszCachePath[path_len] = '\\';
        wszCachePath[path_len+1] = 0;

        strcpyW(wszMutexName, wszCachePath);
        
        if (suffix_len)
        {
            memcpy(wszCachePath + path_len + 1, DefaultContainerData[i].shpath_suffix, (suffix_len + 1) * sizeof(WCHAR));
            wszCachePath[path_len + suffix_len + 1] = '\\';
            wszCachePath[path_len + suffix_len + 2] = '\0';
        }

        if (!WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS, wszCachePath, path_len,
                    NULL, 0, NULL, &def_char) || def_char)
        {
            WCHAR tmp[MAX_PATH];

            /* cannot convert path to ANSI code page */
            if (!(path_len = GetShortPathNameW(wszCachePath, tmp, MAX_PATH)) ||
                !WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS, tmp, path_len,
                    NULL, 0, NULL, &def_char) || def_char)
                ERR("Can't create container path accessible by ANSI functions\n");
            else
                memcpy(wszCachePath, tmp, (path_len+1)*sizeof(WCHAR));
        }

        cache_containers_add(DefaultContainerData[i].cache_prefix, wszCachePath,
                DefaultContainerData[i].default_entry_type, wszMutexName);
    }

#ifdef __REACTOS__
    bDefaultContainersAdded = TRUE;
#endif
}