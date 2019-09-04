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
struct simple_pattern {size_t len; int mode; struct simple_pattern* child; int /*<<< orphan*/  match; } ;

/* Variables and functions */
#define  SIMPLE_PATTERN_EXACT 131 
#define  SIMPLE_PATTERN_PREFIX 130 
#define  SIMPLE_PATTERN_SUBSTRING 129 
#define  SIMPLE_PATTERN_SUFFIX 128 
 char* add_wildcarded (char const*,size_t,char*,size_t*) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (char const*,int /*<<< orphan*/ ,size_t) ; 
 char* strstr (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlikely (int) ; 

__attribute__((used)) static inline int match_pattern(struct simple_pattern *m, const char *str, size_t len, char *wildcarded, size_t *wildcarded_size) {
    char *s;

    if(m->len <= len) {
        switch(m->mode) {
            case SIMPLE_PATTERN_SUBSTRING:
                if(!m->len) return 1;
                if((s = strstr(str, m->match))) {
                    wildcarded = add_wildcarded(str, s - str, wildcarded, wildcarded_size);
                    if(!m->child) {
                        wildcarded = add_wildcarded(&s[m->len], len - (&s[m->len] - str), wildcarded, wildcarded_size);
                        return 1;
                    }
                    return match_pattern(m->child, &s[m->len], len - (s - str) - m->len, wildcarded, wildcarded_size);
                }
                break;

            case SIMPLE_PATTERN_PREFIX:
                if(unlikely(strncmp(str, m->match, m->len) == 0)) {
                    if(!m->child) {
                        wildcarded = add_wildcarded(&str[m->len], len - m->len, wildcarded, wildcarded_size);
                        return 1;
                    }
                    return match_pattern(m->child, &str[m->len], len - m->len, wildcarded, wildcarded_size);
                }
                break;

            case SIMPLE_PATTERN_SUFFIX:
                if(unlikely(strcmp(&str[len - m->len], m->match) == 0)) {
                    wildcarded = add_wildcarded(str, len - m->len, wildcarded, wildcarded_size);
                    if(!m->child) return 1;
                    return 0;
                }
                break;

            case SIMPLE_PATTERN_EXACT:
            default:
                if(unlikely(strcmp(str, m->match) == 0)) {
                    if(!m->child) return 1;
                    return 0;
                }
                break;
        }
    }

    return 0;
}