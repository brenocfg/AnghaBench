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
typedef  char* DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  fourcc_to_string (char*,char*) ; 
 scalar_t__ isalnum (char) ; 
 scalar_t__ isspace (char) ; 
 char const* wine_dbg_sprintf (char*,char*) ; 

__attribute__((used)) static inline const char *wine_dbgstr_fcc( DWORD fcc )
{
    char fcc_str[5];
    fourcc_to_string(fcc_str, fcc);
    fcc_str[4] = '\0';
    /* Last byte may be ' ' in some cases like "DIB " */
    if (isalnum(fcc_str[0]) && isalnum(fcc_str[1]) && isalnum(fcc_str[2])
    && (isalnum(fcc_str[3]) || isspace(fcc_str[3])))
        return wine_dbg_sprintf("%s", fcc_str);
    return wine_dbg_sprintf("0x%08x", fcc);
}