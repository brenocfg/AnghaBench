#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uc ;
struct TYPE_5__ {int /*<<< orphan*/ * proxy; int /*<<< orphan*/ * proxyUsername; int /*<<< orphan*/ * proxyPassword; } ;
typedef  TYPE_1__ proxyinfo_t ;
typedef  char WCHAR ;
struct TYPE_6__ {int member_0; int dwHostNameLength; int dwUserNameLength; int dwPasswordLength; int /*<<< orphan*/  lpszPassword; int /*<<< orphan*/  lpszUserName; int /*<<< orphan*/  nPort; int /*<<< orphan*/  lpszHostName; } ;
typedef  TYPE_2__ URL_COMPONENTSW ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  InternetCrackUrlW (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * heap_strdupW (char const*) ; 
 void* heap_strndupW (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprintfW (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL parse_proxy_url( proxyinfo_t *info, const WCHAR *url )
{
    static const WCHAR fmt[] = {'%','.','*','s',':','%','u',0};
    URL_COMPONENTSW uc = {sizeof(uc)};

    uc.dwHostNameLength = 1;
    uc.dwUserNameLength = 1;
    uc.dwPasswordLength = 1;

    if (!InternetCrackUrlW( url, 0, 0, &uc )) return FALSE;
    if (!uc.dwHostNameLength)
    {
        if (!(info->proxy = heap_strdupW( url ))) return FALSE;
        info->proxyUsername = NULL;
        info->proxyPassword = NULL;
        return TRUE;
    }
    if (!(info->proxy = heap_alloc( (uc.dwHostNameLength + 12) * sizeof(WCHAR) ))) return FALSE;
    sprintfW( info->proxy, fmt, uc.dwHostNameLength, uc.lpszHostName, uc.nPort );

    if (!uc.dwUserNameLength) info->proxyUsername = NULL;
    else if (!(info->proxyUsername = heap_strndupW( uc.lpszUserName, uc.dwUserNameLength )))
    {
        heap_free( info->proxy );
        return FALSE;
    }
    if (!uc.dwPasswordLength) info->proxyPassword = NULL;
    else if (!(info->proxyPassword = heap_strndupW( uc.lpszPassword, uc.dwPasswordLength )))
    {
        heap_free( info->proxyUsername );
        heap_free( info->proxy );
        return FALSE;
    }
    return TRUE;
}