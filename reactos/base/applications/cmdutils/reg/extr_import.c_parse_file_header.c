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
typedef  enum reg_versions { ____Placeholder_reg_versions } reg_versions ;
typedef  char WCHAR ;

/* Variables and functions */
 int REG_VERSION_31 ; 
 int REG_VERSION_40 ; 
 int REG_VERSION_50 ; 
 int REG_VERSION_FUZZY ; 
 int REG_VERSION_INVALID ; 
 int /*<<< orphan*/  strcmpW (char const*,char const*) ; 
 int /*<<< orphan*/  strncmpW (char const*,char const*,int) ; 

__attribute__((used)) static enum reg_versions parse_file_header(const WCHAR *s)
{
    static const WCHAR header_31[] = {'R','E','G','E','D','I','T',0};
    static const WCHAR header_40[] = {'R','E','G','E','D','I','T','4',0};
    static const WCHAR header_50[] = {'W','i','n','d','o','w','s',' ',
                                      'R','e','g','i','s','t','r','y',' ','E','d','i','t','o','r',' ',
                                      'V','e','r','s','i','o','n',' ','5','.','0','0',0};

    while (*s == ' ' || *s == '\t') s++;

    if (!strcmpW(s, header_31))
        return REG_VERSION_31;

    if (!strcmpW(s, header_40))
        return REG_VERSION_40;

    if (!strcmpW(s, header_50))
        return REG_VERSION_50;

    /* The Windows version accepts registry file headers beginning with "REGEDIT" and ending
     * with other characters, as long as "REGEDIT" appears at the start of the line. For example,
     * "REGEDIT 4", "REGEDIT9" and "REGEDIT4FOO" are all treated as valid file headers.
     * In all such cases, however, the contents of the registry file are not imported.
     */
    if (!strncmpW(s, header_31, 7)) /* "REGEDIT" without NUL */
        return REG_VERSION_FUZZY;

    return REG_VERSION_INVALID;
}