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

/* Variables and functions */
 int /*<<< orphan*/  NAMECH ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ strspn (char*,int /*<<< orphan*/ ) ; 
 char* talloc_asprintf_append (char*,char*,scalar_t__,char*) ; 
 char* talloc_strdup_append (char*,char*) ; 

__attribute__((used)) static void append_param(char **res, char *param)
{
    if (strspn(param, NAMECH) == strlen(param)) {
        *res = talloc_strdup_append(*res, param);
    } else {
        // Simple escaping: %BYTECOUNT%STRING
        *res = talloc_asprintf_append(*res, "%%%zd%%%s", strlen(param), param);
    }
}