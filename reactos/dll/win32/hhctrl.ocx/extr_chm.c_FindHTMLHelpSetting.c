#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_5__ {TYPE_1__* pCHMInfo; } ;
struct TYPE_4__ {char const* compiledFile; int /*<<< orphan*/ * pStorage; } ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  IStorage ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_2__ HHInfo ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IStorage_OpenStream (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STGM_READ ; 
 char* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (char*) ; 
 int /*<<< orphan*/  lstrcatW (char*,char const*) ; 
 int /*<<< orphan*/  lstrcpyW (char*,char const*) ; 
 int lstrlenW (char const*) ; 
 char* strdupAtoW (char*) ; 

__attribute__((used)) static WCHAR *FindHTMLHelpSetting(HHInfo *info, const WCHAR *extW)
{
    static const WCHAR periodW[] = {'.',0};
    IStorage *pStorage = info->pCHMInfo->pStorage;
    IStream *pStream;
    WCHAR *filename;
    HRESULT hr;

    filename = heap_alloc( (lstrlenW(info->pCHMInfo->compiledFile)
                            + lstrlenW(periodW) + lstrlenW(extW) + 1) * sizeof(WCHAR) );
    lstrcpyW(filename, info->pCHMInfo->compiledFile);
    lstrcatW(filename, periodW);
    lstrcatW(filename, extW);
    hr = IStorage_OpenStream(pStorage, filename, NULL, STGM_READ, 0, &pStream);
    if (FAILED(hr))
    {
        heap_free(filename);
        return strdupAtoW("");
    }
    IStream_Release(pStream);
    return filename;
}