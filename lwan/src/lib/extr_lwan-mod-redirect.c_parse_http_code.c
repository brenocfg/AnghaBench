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
typedef  enum lwan_http_status { ____Placeholder_lwan_http_status } lwan_http_status ;

/* Variables and functions */
 char* lwan_http_status_as_string_with_code (int) ; 
 int parse_int (char const*,int) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

__attribute__((used)) static enum lwan_http_status parse_http_code(const char *code,
                                             enum lwan_http_status fallback)
{
    const char *known;
    int as_int;

    if (!code)
        return fallback;

    as_int = parse_int(code, 999);
    if (as_int == 999)
        return fallback;

    known = lwan_http_status_as_string_with_code((enum lwan_http_status)as_int);
    if (!strncmp(known, "999", 3))
        return fallback;

    return (enum lwan_http_status)as_int;
}