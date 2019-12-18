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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  IUri ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CreateUri (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  E_FAIL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int INTERNET_MAX_URL_LENGTH ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  PathIsURLW (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  PathSearchAndQualifyW (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int Uri_CREATE_ALLOW_IMPLICIT_FILE_SCHEME ; 
 int Uri_CREATE_ALLOW_RELATIVE ; 
 int /*<<< orphan*/  UrlCreateFromPathW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/  const*) ; 

HRESULT create_uri(const WCHAR *url, IUri **uri)
{
    WCHAR fileUrl[INTERNET_MAX_URL_LENGTH];

    TRACE("%s\n", debugstr_w(url));

    if (!PathIsURLW(url))
    {
        WCHAR fullpath[MAX_PATH];
        DWORD needed = ARRAY_SIZE(fileUrl);

        if (!PathSearchAndQualifyW(url, fullpath, ARRAY_SIZE(fullpath)))
        {
            WARN("can't find path\n");
            return E_FAIL;
        }

        if (FAILED(UrlCreateFromPathW(fullpath, fileUrl, &needed, 0)))
        {
            ERR("can't create url from path\n");
            return E_FAIL;
        }
        url = fileUrl;
    }

    return CreateUri(url, Uri_CREATE_ALLOW_RELATIVE | Uri_CREATE_ALLOW_IMPLICIT_FILE_SCHEME, 0, uri);
}