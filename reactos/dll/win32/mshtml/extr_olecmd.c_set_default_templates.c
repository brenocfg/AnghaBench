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
typedef  int /*<<< orphan*/  nsIPrintSettings ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  PRUnichar ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IDS_PRINT_FOOTER_TEMPLATE ; 
 int /*<<< orphan*/  IDS_PRINT_HEADER_TEMPLATE ; 
 scalar_t__ LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  get_shdoclc () ; 
 int /*<<< orphan*/  nsIPrintSettings_SetFooterStrCenter (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  nsIPrintSettings_SetFooterStrLeft (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  nsIPrintSettings_SetFooterStrRight (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  nsIPrintSettings_SetHeaderStrCenter (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  nsIPrintSettings_SetHeaderStrLeft (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  nsIPrintSettings_SetHeaderStrRight (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  set_print_template (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_default_templates(nsIPrintSettings *settings)
{
    WCHAR buf[64];

    static const PRUnichar empty[] = {0};

    nsIPrintSettings_SetHeaderStrLeft(settings, empty);
    nsIPrintSettings_SetHeaderStrRight(settings, empty);
    nsIPrintSettings_SetHeaderStrCenter(settings, empty);
    nsIPrintSettings_SetFooterStrLeft(settings, empty);
    nsIPrintSettings_SetFooterStrRight(settings, empty);
    nsIPrintSettings_SetFooterStrCenter(settings, empty);

    if(LoadStringW(get_shdoclc(), IDS_PRINT_HEADER_TEMPLATE, buf,
                   sizeof(buf)/sizeof(WCHAR)))
        set_print_template(settings, buf, TRUE);


    if(LoadStringW(get_shdoclc(), IDS_PRINT_FOOTER_TEMPLATE, buf,
                   sizeof(buf)/sizeof(WCHAR)))
        set_print_template(settings, buf, FALSE);

}