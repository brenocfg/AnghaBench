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
 int /*<<< orphan*/  config_parse_duration (char*,int*) ; 
 int /*<<< orphan*/  error (char*,size_t,char const*,char*,...) ; 
 scalar_t__ isinf (float) ; 
 scalar_t__ islessequal (float,int /*<<< orphan*/ ) ; 
 scalar_t__ isnan (float) ; 
 scalar_t__ isspace (char) ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 
 float strtof (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int health_parse_delay(
        size_t line, const char *filename, char *string,
        int *delay_up_duration,
        int *delay_down_duration,
        int *delay_max_duration,
        float *delay_multiplier) {

    char given_up = 0;
    char given_down = 0;
    char given_max = 0;
    char given_multiplier = 0;

    char *s = string;
    while(*s) {
        char *key = s;

        while(*s && !isspace(*s)) s++;
        while(*s && isspace(*s)) *s++ = '\0';

        if(!*key) break;

        char *value = s;
        while(*s && !isspace(*s)) s++;
        while(*s && isspace(*s)) *s++ = '\0';

        if(!strcasecmp(key, "up")) {
            if (!config_parse_duration(value, delay_up_duration)) {
                error("Health configuration at line %zu of file '%s': invalid value '%s' for '%s' keyword",
                        line, filename, value, key);
            }
            else given_up = 1;
        }
        else if(!strcasecmp(key, "down")) {
            if (!config_parse_duration(value, delay_down_duration)) {
                error("Health configuration at line %zu of file '%s': invalid value '%s' for '%s' keyword",
                        line, filename, value, key);
            }
            else given_down = 1;
        }
        else if(!strcasecmp(key, "multiplier")) {
            *delay_multiplier = strtof(value, NULL);
            if(isnan(*delay_multiplier) || isinf(*delay_multiplier) || islessequal(*delay_multiplier, 0)) {
                error("Health configuration at line %zu of file '%s': invalid value '%s' for '%s' keyword",
                        line, filename, value, key);
            }
            else given_multiplier = 1;
        }
        else if(!strcasecmp(key, "max")) {
            if (!config_parse_duration(value, delay_max_duration)) {
                error("Health configuration at line %zu of file '%s': invalid value '%s' for '%s' keyword",
                        line, filename, value, key);
            }
            else given_max = 1;
        }
        else {
            error("Health configuration at line %zu of file '%s': unknown keyword '%s'",
                    line, filename, key);
        }
    }

    if(!given_up)
        *delay_up_duration = 0;

    if(!given_down)
        *delay_down_duration = 0;

    if(!given_multiplier)
        *delay_multiplier = 1.0;

    if(!given_max) {
        if((*delay_max_duration) < (*delay_up_duration) * (*delay_multiplier))
            *delay_max_duration = (int)((*delay_up_duration) * (*delay_multiplier));

        if((*delay_max_duration) < (*delay_down_duration) * (*delay_multiplier))
            *delay_max_duration = (int)((*delay_down_duration) * (*delay_multiplier));
    }

    return 1;
}