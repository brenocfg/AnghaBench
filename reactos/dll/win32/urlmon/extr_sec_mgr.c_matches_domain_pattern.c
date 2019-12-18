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
typedef  char WCHAR ;
typedef  char* LPCWSTR ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  debugstr_w (char*) ; 
 char* memrchrW (char*,char,scalar_t__) ; 
 int /*<<< orphan*/  strcmpiW (char*,char*) ; 
 scalar_t__ strlenW (char*) ; 

__attribute__((used)) static BOOL matches_domain_pattern(LPCWSTR pattern, LPCWSTR str, BOOL implicit_wildcard, LPCWSTR *matched)
{
    BOOL matches = FALSE;
    DWORD pattern_len = strlenW(pattern);
    DWORD str_len = strlenW(str);

    TRACE("(%d) Checking if %s matches %s\n", implicit_wildcard, debugstr_w(str), debugstr_w(pattern));

    *matched = NULL;
    if(str_len >= pattern_len) {
        /* Check if there's an explicit wildcard in the pattern. */
        if(pattern[0] == '*' && pattern[1] == '.') {
            /* Make sure that 'str' matches the wildcard pattern.
             *
             * Example:
             *  pattern = "*.google.com"
             *
             * So in this case 'str' would have to end with ".google.com" in order
             * to map to this pattern.
             */
            if(str_len >= pattern_len+1 && !strcmpiW(str+(str_len-pattern_len+1), pattern+1)) {
                /* Check if there's another '.' inside of the "unmatched" portion
                 * of 'str'.
                 *
                 * Example:
                 *  pattern = "*.google.com"
                 *  str     = "test.testing.google.com"
                 *
                 * The currently matched portion is ".google.com" in 'str', we need
                 * see if there's a '.' inside of the unmatched portion ("test.testing"), because
                 * if there is and 'implicit_wildcard' isn't set, then this isn't
                 * a match.
                 */
                const WCHAR *ptr;
                if(str_len > pattern_len+1 && (ptr = memrchrW(str, '.', str_len-pattern_len-2))) {
                    if(implicit_wildcard) {
                        matches = TRUE;
                        *matched = ptr+1;
                    }
                } else {
                    matches = TRUE;
                    *matched = str;
                }
            }
        } else if(implicit_wildcard && str_len > pattern_len) {
            /* When the pattern has an implicit wildcard component, it means
             * that anything goes in 'str' as long as it ends with the pattern
             * and that the beginning of the match has a '.' before it.
             *
             * Example:
             *  pattern = "google.com"
             *  str     = "www.google.com"
             *
             * Implicitly matches the pattern, where as:
             *
             *  pattern = "google.com"
             *  str     = "wwwgoogle.com"
             *
             * Doesn't match the pattern.
             */
            if(str[str_len-pattern_len-1] == '.' && !strcmpiW(str+(str_len-pattern_len), pattern)) {
                matches = TRUE;
                *matched = str+(str_len-pattern_len);
            }
        } else {
            /* The pattern doesn't have an implicit wildcard, or an explicit wildcard,
             * so 'str' has to be an exact match to the 'pattern'.
             */
            if(!strcmpiW(str, pattern)) {
                matches = TRUE;
                *matched = str;
            }
        }
    }

    if(matches)
        TRACE("Found a match: matched=%s\n", debugstr_w(*matched));
    else
        TRACE("No match found\n");

    return matches;
}