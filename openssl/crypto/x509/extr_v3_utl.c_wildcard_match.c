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
 unsigned int X509_CHECK_FLAG_MULTI_LABEL_WILDCARDS ; 
 int /*<<< orphan*/  equal_nocase (unsigned char const*,size_t,unsigned char const*,size_t,unsigned int) ; 
 scalar_t__ strncasecmp (char*,char*,int) ; 

__attribute__((used)) static int wildcard_match(const unsigned char *prefix, size_t prefix_len,
                          const unsigned char *suffix, size_t suffix_len,
                          const unsigned char *subject, size_t subject_len,
                          unsigned int flags)
{
    const unsigned char *wildcard_start;
    const unsigned char *wildcard_end;
    const unsigned char *p;
    int allow_multi = 0;
    int allow_idna = 0;

    if (subject_len < prefix_len + suffix_len)
        return 0;
    if (!equal_nocase(prefix, prefix_len, subject, prefix_len, flags))
        return 0;
    wildcard_start = subject + prefix_len;
    wildcard_end = subject + (subject_len - suffix_len);
    if (!equal_nocase(wildcard_end, suffix_len, suffix, suffix_len, flags))
        return 0;
    /*
     * If the wildcard makes up the entire first label, it must match at
     * least one character.
     */
    if (prefix_len == 0 && *suffix == '.') {
        if (wildcard_start == wildcard_end)
            return 0;
        allow_idna = 1;
        if (flags & X509_CHECK_FLAG_MULTI_LABEL_WILDCARDS)
            allow_multi = 1;
    }
    /* IDNA labels cannot match partial wildcards */
    if (!allow_idna &&
        subject_len >= 4 && strncasecmp((char *)subject, "xn--", 4) == 0)
        return 0;
    /* The wildcard may match a literal '*' */
    if (wildcard_end == wildcard_start + 1 && *wildcard_start == '*')
        return 1;
    /*
     * Check that the part matched by the wildcard contains only
     * permitted characters and only matches a single label unless
     * allow_multi is set.
     */
    for (p = wildcard_start; p != wildcard_end; ++p)
        if (!(('0' <= *p && *p <= '9') ||
              ('A' <= *p && *p <= 'Z') ||
              ('a' <= *p && *p <= 'z') ||
              *p == '-' || (allow_multi && *p == '.')))
            return 0;
    return 1;
}