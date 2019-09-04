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
struct simple_pattern {char* match; struct simple_pattern* child; void* mode; void* len; } ;
typedef  void* SIMPLE_PREFIX_MODE ;

/* Variables and functions */
 void* SIMPLE_PATTERN_PREFIX ; 
 void* SIMPLE_PATTERN_SUBSTRING ; 
 void* SIMPLE_PATTERN_SUFFIX ; 
 struct simple_pattern* callocz (int,int) ; 
 char* strdupz (char*) ; 
 void* strlen (char*) ; 

__attribute__((used)) static inline struct simple_pattern *parse_pattern(char *str, SIMPLE_PREFIX_MODE default_mode) {
    // fprintf(stderr, "PARSING PATTERN: '%s'\n", str);

    SIMPLE_PREFIX_MODE mode;
    struct simple_pattern *child = NULL;

    char *s = str, *c = str;

    // skip asterisks in front
    while(*c == '*') c++;

    // find the next asterisk
    while(*c && *c != '*') c++;

    // do we have an asterisk in the middle?
    if(*c == '*' && c[1] != '\0') {
        // yes, we have
        child = parse_pattern(c, default_mode);
        c[1] = '\0';
    }

    // check what this one matches

    size_t len = strlen(s);
    if(len >= 2 && *s == '*' && s[len - 1] == '*') {
        s[len - 1] = '\0';
        s++;
        mode = SIMPLE_PATTERN_SUBSTRING;
    }
    else if(len >= 1 && *s == '*') {
        s++;
        mode = SIMPLE_PATTERN_SUFFIX;
    }
    else if(len >= 1 && s[len - 1] == '*') {
        s[len - 1] = '\0';
        mode = SIMPLE_PATTERN_PREFIX;
    }
    else
        mode = default_mode;

    // allocate the structure
    struct simple_pattern *m = callocz(1, sizeof(struct simple_pattern));
    if(*s) {
        m->match = strdupz(s);
        m->len = strlen(m->match);
        m->mode = mode;
    }
    else {
        m->mode = SIMPLE_PATTERN_SUBSTRING;
    }

    m->child = child;

    return m;
}