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
typedef  int /*<<< orphan*/  SYSTEMTIME ;
typedef  int /*<<< orphan*/  IDxDiagContainerImpl_Container ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char*) ; 
 int /*<<< orphan*/  DATE_LONGDATE ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDateFormatW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetLocalTime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetTimeFormatW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCALE_NEUTRAL ; 
 int /*<<< orphan*/  LOCALE_USER_DEFAULT ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  add_bstr_property (int /*<<< orphan*/ *,char const*,char*) ; 
 int /*<<< orphan*/  swprintf (char*,char const*,char*,char*) ; 

__attribute__((used)) static HRESULT fill_datetime_information(IDxDiagContainerImpl_Container *node)
{
    static const WCHAR date_fmtW[] = {'M','\'','/','\'','d','\'','/','\'','y','y','y','y',0};
    static const WCHAR time_fmtW[] = {'H','H','\'',':','\'','m','m','\'',':','\'','s','s',0};
    static const WCHAR datetime_fmtW[] = {'%','s',',',' ','%','s',0};
    static const WCHAR szTimeLocalized[] = {'s','z','T','i','m','e','L','o','c','a','l','i','z','e','d',0};
    static const WCHAR szTimeEnglish[] = {'s','z','T','i','m','e','E','n','g','l','i','s','h',0};

    SYSTEMTIME curtime;
    WCHAR date_str[80], time_str[80], datetime_str[200];
    HRESULT hr;

    GetLocalTime(&curtime);

    GetTimeFormatW(LOCALE_NEUTRAL, 0, &curtime, time_fmtW, time_str, ARRAY_SIZE(time_str));

    /* szTimeLocalized */
    GetDateFormatW(LOCALE_USER_DEFAULT, DATE_LONGDATE, &curtime, NULL, date_str, ARRAY_SIZE(date_str));

    swprintf(datetime_str, datetime_fmtW, date_str, time_str);

    hr = add_bstr_property(node, szTimeLocalized, datetime_str);
    if (FAILED(hr))
        return hr;

    /* szTimeEnglish */
    GetDateFormatW(LOCALE_NEUTRAL, 0, &curtime, date_fmtW, date_str, ARRAY_SIZE(date_str));

    swprintf(datetime_str, datetime_fmtW, date_str, time_str);

    hr = add_bstr_property(node, szTimeEnglish, datetime_str);
    if (FAILED(hr))
        return hr;

    return S_OK;
}