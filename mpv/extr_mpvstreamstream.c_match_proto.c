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
 int /*<<< orphan*/  bstr0 (char const*) ; 
 int /*<<< orphan*/  mp_is_url (int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 
 scalar_t__ strncasecmp (char const*,char const*,int) ; 
 scalar_t__ strncmp (char*,char const*,int) ; 

__attribute__((used)) static const char *match_proto(const char *url, const char *proto)
{
    int l = strlen(proto);
    if (l > 0) {
        if (strncasecmp(url, proto, l) == 0 && strncmp("://", url + l, 3) == 0)
            return url + l + 3;
    } else if (!mp_is_url(bstr0(url))) {
        return url; // pure filenames
    }
    return NULL;
}