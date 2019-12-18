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

/* Variables and functions */
 int /*<<< orphan*/  CoInternetCombineUrlEx (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_FAIL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IUri_Release (int /*<<< orphan*/ *) ; 
 int URL_DONT_ESCAPE_EXTRA_INFO ; 
 int URL_ESCAPE_SPACES_ONLY ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_uri_nofrag (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT combine_url(IUri *base_uri, const WCHAR *rel_url, IUri **ret)
{
    IUri *uri_nofrag;
    HRESULT hres;

    uri_nofrag = get_uri_nofrag(base_uri);
    if(!uri_nofrag)
        return E_FAIL;

    hres = CoInternetCombineUrlEx(uri_nofrag, rel_url, URL_ESCAPE_SPACES_ONLY|URL_DONT_ESCAPE_EXTRA_INFO,
                ret, 0);
    IUri_Release(uri_nofrag);
    if(FAILED(hres))
        WARN("CoInternetCombineUrlEx failed: %08x\n", hres);
    return hres;
}