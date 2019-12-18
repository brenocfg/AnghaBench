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
 int equal_nocase (unsigned char const*,size_t,unsigned char const*,size_t,unsigned int) ; 
 unsigned char* valid_star (unsigned char const*,size_t,unsigned int) ; 
 int wildcard_match (unsigned char const*,int,unsigned char const*,int,unsigned char const*,size_t,unsigned int) ; 

__attribute__((used)) static int equal_wildcard(const unsigned char *pattern, size_t pattern_len,
                          const unsigned char *subject, size_t subject_len,
                          unsigned int flags)
{
    const unsigned char *star = NULL;

    /*
     * Subject names starting with '.' can only match a wildcard pattern
     * via a subject sub-domain pattern suffix match.
     */
    if (!(subject_len > 1 && subject[0] == '.'))
        star = valid_star(pattern, pattern_len, flags);
    if (star == NULL)
        return equal_nocase(pattern, pattern_len,
                            subject, subject_len, flags);
    return wildcard_match(pattern, star - pattern,
                          star + 1, (pattern + pattern_len) - star - 1,
                          subject, subject_len, flags);
}