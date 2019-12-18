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
typedef  int /*<<< orphan*/  IDxDiagContainerImpl_Container ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char*) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetLocaleInfoW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDS_REGIONAL_SETTING ; 
 int /*<<< orphan*/  LOCALE_SENGLANGUAGE ; 
 int /*<<< orphan*/  LOCALE_SNATIVELANGNAME ; 
 int /*<<< orphan*/  LOCALE_SYSTEM_DEFAULT ; 
 int /*<<< orphan*/  LOCALE_USER_DEFAULT ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  add_bstr_property (int /*<<< orphan*/ *,char const*,char*) ; 
 int /*<<< orphan*/  dxdiagn_instance ; 
 int /*<<< orphan*/  swprintf (char*,char const*,char*,char const*,char*) ; 

__attribute__((used)) static HRESULT fill_language_information(IDxDiagContainerImpl_Container *node)
{
    static const WCHAR regional_setting_engW[] = {'R','e','g','i','o','n','a','l',' ','S','e','t','t','i','n','g',0};
    static const WCHAR languages_fmtW[] = {'%','s',' ','(','%','s',':',' ','%','s',')',0};
    static const WCHAR szLanguagesLocalized[] = {'s','z','L','a','n','g','u','a','g','e','s','L','o','c','a','l','i','z','e','d',0};
    static const WCHAR szLanguagesEnglish[] = {'s','z','L','a','n','g','u','a','g','e','s','E','n','g','l','i','s','h',0};

    WCHAR system_lang[80], regional_setting[100], user_lang[80], language_str[300];
    HRESULT hr;

    /* szLanguagesLocalized */
    GetLocaleInfoW(LOCALE_SYSTEM_DEFAULT, LOCALE_SNATIVELANGNAME, system_lang, ARRAY_SIZE(system_lang));
    LoadStringW(dxdiagn_instance, IDS_REGIONAL_SETTING, regional_setting, ARRAY_SIZE(regional_setting));
    GetLocaleInfoW(LOCALE_USER_DEFAULT, LOCALE_SNATIVELANGNAME, user_lang, ARRAY_SIZE(user_lang));

    swprintf(language_str, languages_fmtW, system_lang, regional_setting,
              user_lang);

    hr = add_bstr_property(node, szLanguagesLocalized, language_str);
    if (FAILED(hr))
        return hr;

    /* szLanguagesEnglish */
    GetLocaleInfoW(LOCALE_SYSTEM_DEFAULT, LOCALE_SENGLANGUAGE, system_lang, ARRAY_SIZE(system_lang));
    GetLocaleInfoW(LOCALE_USER_DEFAULT, LOCALE_SENGLANGUAGE, user_lang, ARRAY_SIZE(user_lang));

    swprintf(language_str, languages_fmtW, system_lang,
              regional_setting_engW, user_lang);

    hr = add_bstr_property(node, szLanguagesEnglish, language_str);
    if (FAILED(hr))
        return hr;

    return S_OK;
}