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
 char* mymalloc (scalar_t__) ; 
 scalar_t__ urlcount (char const*,char const*) ; 
 int /*<<< orphan*/  urlencode (char const*,char*,char const*) ; 

char *
CGI_encode_url(const char *p, const char *keep) {
    char *out;

    if (p == 0) {
        return 0;
    }
    out = mymalloc(urlcount(p, keep) + 1);
    urlencode(p, out, keep);
    return out;
}