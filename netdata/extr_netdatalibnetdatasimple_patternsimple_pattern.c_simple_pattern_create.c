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
struct simple_pattern {char negative; struct simple_pattern* next; } ;
typedef  int /*<<< orphan*/  isseparator ;
typedef  int /*<<< orphan*/  SIMPLE_PREFIX_MODE ;
typedef  struct simple_pattern SIMPLE_PATTERN ;

/* Variables and functions */
 int /*<<< orphan*/  freez (char*) ; 
 char* mallocz (scalar_t__) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 struct simple_pattern* parse_pattern (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ unlikely (int) ; 

SIMPLE_PATTERN *simple_pattern_create(const char *list, const char *separators, SIMPLE_PREFIX_MODE default_mode) {
    struct simple_pattern *root = NULL, *last = NULL;

    if(unlikely(!list || !*list)) return root;

    int isseparator[256] = {
            [' '] = 1       // space
            , ['\t'] = 1    // tab
            , ['\r'] = 1    // carriage return
            , ['\n'] = 1    // new line
            , ['\f'] = 1    // form feed
            , ['\v'] = 1    // vertical tab
    };

    if (unlikely(separators && *separators)) {
        memset(&isseparator[0], 0, sizeof(isseparator));
        while(*separators) isseparator[(unsigned char)*separators++] = 1;
    }

    char *buf = mallocz(strlen(list) + 1);
    const char *s = list;

    while(s && *s) {
        buf[0] = '\0';
        char *c = buf;

        char negative = 0;

        // skip all spaces
        while(isseparator[(unsigned char)*s])
            s++;

        if(*s == '!') {
            negative = 1;
            s++;
        }

        // empty string
        if(unlikely(!*s))
            break;

        // find the next space
        char escape = 0;
        while(*s) {
            if(*s == '\\' && !escape) {
                escape = 1;
                s++;
            }
            else {
                if (isseparator[(unsigned char)*s] && !escape) {
                    s++;
                    break;
                }

                *c++ = *s++;
                escape = 0;
            }
        }

        // terminate our string
        *c = '\0';

        // if we matched the empty string, skip it
        if(unlikely(!*buf))
            continue;

        // fprintf(stderr, "FOUND PATTERN: '%s'\n", buf);
        struct simple_pattern *m = parse_pattern(buf, default_mode);
        m->negative = negative;

        // link it at the end
        if(unlikely(!root))
            root = last = m;
        else {
            last->next = m;
            last = m;
        }
    }

    freez(buf);
    return (SIMPLE_PATTERN *)root;
}