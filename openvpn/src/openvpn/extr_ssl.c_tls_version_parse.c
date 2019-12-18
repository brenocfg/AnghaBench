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
 int const TLS_VER_1_0 ; 
 int const TLS_VER_1_1 ; 
 int const TLS_VER_1_2 ; 
 int const TLS_VER_1_3 ; 
 int TLS_VER_BAD ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int tls_version_max () ; 

int
tls_version_parse(const char *vstr, const char *extra)
{
    const int max_version = tls_version_max();
    if (!strcmp(vstr, "1.0") && TLS_VER_1_0 <= max_version)
    {
        return TLS_VER_1_0;
    }
    else if (!strcmp(vstr, "1.1") && TLS_VER_1_1 <= max_version)
    {
        return TLS_VER_1_1;
    }
    else if (!strcmp(vstr, "1.2") && TLS_VER_1_2 <= max_version)
    {
        return TLS_VER_1_2;
    }
    else if (!strcmp(vstr, "1.3") && TLS_VER_1_3 <= max_version)
    {
        return TLS_VER_1_3;
    }
    else if (extra && !strcmp(extra, "or-highest"))
    {
        return max_version;
    }
    else
    {
        return TLS_VER_BAD;
    }
}