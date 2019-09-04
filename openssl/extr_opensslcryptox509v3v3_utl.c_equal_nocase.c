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
 int /*<<< orphan*/  skip_prefix (unsigned char const**,size_t*,size_t,unsigned int) ; 

__attribute__((used)) static int equal_nocase(const unsigned char *pattern, size_t pattern_len,
                        const unsigned char *subject, size_t subject_len,
                        unsigned int flags)
{
    skip_prefix(&pattern, &pattern_len, subject_len, flags);
    if (pattern_len != subject_len)
        return 0;
    while (pattern_len) {
        unsigned char l = *pattern;
        unsigned char r = *subject;
        /* The pattern must not contain NUL characters. */
        if (l == 0)
            return 0;
        if (l != r) {
            if ('A' <= l && l <= 'Z')
                l = (l - 'A') + 'a';
            if ('A' <= r && r <= 'Z')
                r = (r - 'A') + 'a';
            if (l != r)
                return 0;
        }
        ++pattern;
        ++subject;
        --pattern_len;
    }
    return 1;
}