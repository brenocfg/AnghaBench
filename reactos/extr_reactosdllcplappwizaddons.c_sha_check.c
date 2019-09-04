#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sha ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_2__ {int /*<<< orphan*/  sha; } ;
typedef  int /*<<< orphan*/  SHA_CTX ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  A_SHAFinal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  A_SHAInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  A_SHAUpdate (int /*<<< orphan*/ *,unsigned char const*,int) ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileMappingW (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ CreateFileW (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_READONLY ; 
 int /*<<< orphan*/  FILE_MAP_READ ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 int GetFileSize (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 unsigned char* MapViewOfFile (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  PAGE_READONLY ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UnmapViewOfFile (unsigned char const*) ; 
 int /*<<< orphan*/  WARN (char*,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* addon ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned char) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL sha_check(const WCHAR *file_name)
{
    const unsigned char *file_map;
    HANDLE file, map;
    ULONG sha[5];
    char buf[2*sizeof(sha)+1];
    SHA_CTX ctx;
    DWORD size, i;

    file = CreateFileW(file_name, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL);
    if(file == INVALID_HANDLE_VALUE)
        return FALSE;

    size = GetFileSize(file, NULL);

    map = CreateFileMappingW(file, NULL, PAGE_READONLY, 0, 0, NULL);
    CloseHandle(file);
    if(!map)
        return FALSE;

    file_map = MapViewOfFile(map, FILE_MAP_READ, 0, 0, 0);
    CloseHandle(map);
    if(!file_map)
        return FALSE;

    A_SHAInit(&ctx);
    A_SHAUpdate(&ctx, file_map, size);
    A_SHAFinal(&ctx, sha);

    UnmapViewOfFile(file_map);

    for(i=0; i < sizeof(sha); i++)
        sprintf(buf + i*2, "%02x", *((unsigned char*)sha+i));

    if(strcmp(buf, addon->sha)) {
        WARN("Got %s, expected %s\n", buf, addon->sha);
        return FALSE;
    }

    return TRUE;
}