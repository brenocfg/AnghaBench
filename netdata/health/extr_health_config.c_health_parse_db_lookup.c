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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  RRDR_GROUPING ;

/* Variables and functions */
 int /*<<< orphan*/  D_HEALTH ; 
 char* HEALTH_EVERY_KEY ; 
 char* HEALTH_FOREACH_KEY ; 
 int /*<<< orphan*/  RRDR_GROUPING_UNDEFINED ; 
 int /*<<< orphan*/  RRDR_OPTION_ABSOLUTE ; 
 int /*<<< orphan*/  RRDR_OPTION_MATCH_IDS ; 
 int /*<<< orphan*/  RRDR_OPTION_MATCH_NAMES ; 
 int /*<<< orphan*/  RRDR_OPTION_MIN2MAX ; 
 int /*<<< orphan*/  RRDR_OPTION_NOT_ALIGNED ; 
 int /*<<< orphan*/  RRDR_OPTION_NULL2ZERO ; 
 int /*<<< orphan*/  RRDR_OPTION_PERCENTAGE ; 
 int abs (int) ; 
 int /*<<< orphan*/  config_parse_duration (char*,int*) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,size_t,char const*,char*) ; 
 int /*<<< orphan*/  error (char*,size_t,char const*,char*,...) ; 
 int /*<<< orphan*/  freez (char*) ; 
 scalar_t__ isspace (char) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 char* strcasestr (char*,char*) ; 
 char* strdupz (char*) ; 
 int /*<<< orphan*/  web_client_api_request_v1_data_group (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int health_parse_db_lookup(
        size_t line, const char *filename, char *string,
        RRDR_GROUPING *group_method, int *after, int *before, int *every,
        uint32_t *options, char **dimensions, char **foreachdim
) {
    debug(D_HEALTH, "Health configuration parsing database lookup %zu@%s: %s", line, filename, string);

    if(*dimensions) freez(*dimensions);
    if(*foreachdim) freez(*foreachdim);
    *dimensions = NULL;
    *foreachdim = NULL;
    *after = 0;
    *before = 0;
    *every = 0;
    *options = 0;

    char *s = string, *key;

    // first is the group method
    key = s;
    while(*s && !isspace(*s)) s++;
    while(*s && isspace(*s)) *s++ = '\0';
    if(!*s) {
        error("Health configuration invalid chart calculation at line %zu of file '%s': expected group method followed by the 'after' time, but got '%s'",
                line, filename, key);
        return 0;
    }

    if((*group_method = web_client_api_request_v1_data_group(key, RRDR_GROUPING_UNDEFINED)) == RRDR_GROUPING_UNDEFINED) {
        error("Health configuration at line %zu of file '%s': invalid group method '%s'",
                line, filename, key);
        return 0;
    }

    // then is the 'after' time
    key = s;
    while(*s && !isspace(*s)) s++;
    while(*s && isspace(*s)) *s++ = '\0';

    if(!config_parse_duration(key, after)) {
        error("Health configuration at line %zu of file '%s': invalid duration '%s' after group method",
                line, filename, key);
        return 0;
    }

    // sane defaults
    *every = abs(*after);

    // now we may have optional parameters
    while(*s) {
        key = s;
        while(*s && !isspace(*s)) s++;
        while(*s && isspace(*s)) *s++ = '\0';
        if(!*key) break;

        if(!strcasecmp(key, "at")) {
            char *value = s;
            while(*s && !isspace(*s)) s++;
            while(*s && isspace(*s)) *s++ = '\0';

            if (!config_parse_duration(value, before)) {
                error("Health configuration at line %zu of file '%s': invalid duration '%s' for '%s' keyword",
                        line, filename, value, key);
            }
        }
        else if(!strcasecmp(key, HEALTH_EVERY_KEY)) {
            char *value = s;
            while(*s && !isspace(*s)) s++;
            while(*s && isspace(*s)) *s++ = '\0';

            if (!config_parse_duration(value, every)) {
                error("Health configuration at line %zu of file '%s': invalid duration '%s' for '%s' keyword",
                        line, filename, value, key);
            }
        }
        else if(!strcasecmp(key, "absolute") || !strcasecmp(key, "abs") || !strcasecmp(key, "absolute_sum")) {
            *options |= RRDR_OPTION_ABSOLUTE;
        }
        else if(!strcasecmp(key, "min2max")) {
            *options |= RRDR_OPTION_MIN2MAX;
        }
        else if(!strcasecmp(key, "null2zero")) {
            *options |= RRDR_OPTION_NULL2ZERO;
        }
        else if(!strcasecmp(key, "percentage")) {
            *options |= RRDR_OPTION_PERCENTAGE;
        }
        else if(!strcasecmp(key, "unaligned")) {
            *options |= RRDR_OPTION_NOT_ALIGNED;
        }
        else if(!strcasecmp(key, "match-ids") || !strcasecmp(key, "match_ids")) {
            *options |= RRDR_OPTION_MATCH_IDS;
        }
        else if(!strcasecmp(key, "match-names") || !strcasecmp(key, "match_names")) {
            *options |= RRDR_OPTION_MATCH_NAMES;
        }
        else if(!strcasecmp(key, "of")) {
            char *find = NULL;
            if(*s && strcasecmp(s, "all") != 0) {
                find = strcasestr(s, " foreach");
                if(find) {
                    *find = '\0';
                }
                *dimensions = strdupz(s);
            }

            if(!find) {
                break;
            }
            s = ++find;
        }
        else if(!strcasecmp(key, HEALTH_FOREACH_KEY )) {
            *foreachdim = strdupz(s);
            break;
        }
        else {
            error("Health configuration at line %zu of file '%s': unknown keyword '%s'",
                    line, filename, key);
        }
    }

    return 1;
}