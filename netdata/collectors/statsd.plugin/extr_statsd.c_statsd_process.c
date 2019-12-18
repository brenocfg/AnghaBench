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
 int /*<<< orphan*/  D_STATSD ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,size_t,char*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memmove (char*,char const*,size_t) ; 
 int /*<<< orphan*/  statsd_parse_field_trim (char const*,char*) ; 
 char* statsd_parse_skip_spaces (char const*) ; 
 scalar_t__ statsd_parse_skip_up_to (char const*,char,char) ; 
 int /*<<< orphan*/  statsd_process_metric (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline size_t statsd_process(char *buffer, size_t size, int require_newlines) {
    buffer[size] = '\0';
    debug(D_STATSD, "RECEIVED: %zu bytes: '%s'", size, buffer);

    const char *s = buffer;
    while(*s) {
        const char *name = NULL, *value = NULL, *type = NULL, *sampling = NULL, *tags = NULL;
        char *name_end = NULL, *value_end = NULL, *type_end = NULL, *sampling_end = NULL, *tags_end = NULL;

        s = name_end = (char *)statsd_parse_skip_up_to(name = s, ':', '|');
        if(name == name_end) {
            s = statsd_parse_skip_spaces(s);
            continue;
        }

        if(likely(*s == ':'))
            s = value_end = (char *) statsd_parse_skip_up_to(value = ++s, '|', '|');

        if(likely(*s == '|'))
            s = type_end = (char *) statsd_parse_skip_up_to(type = ++s, '|', '@');

        if(likely(*s == '|' || *s == '@')) {
            s = sampling_end = (char *) statsd_parse_skip_up_to(sampling = ++s, '|', '#');
            if(*sampling == '@') sampling++;
        }

        if(likely(*s == '|' || *s == '#')) {
            s = tags_end = (char *) statsd_parse_skip_up_to(tags = ++s, '|', '|');
            if(*tags == '#') tags++;
        }

        // skip everything until the end of the line
        while(*s && *s != '\n') s++;

        if(unlikely(require_newlines && *s != '\n' && s > buffer)) {
            // move the remaining data to the beginning
            size -= (name - buffer);
            memmove(buffer, name, size);
            return size;
        }
        else
            s = statsd_parse_skip_spaces(s);

        statsd_process_metric(
                  statsd_parse_field_trim(name, name_end)
                , statsd_parse_field_trim(value, value_end)
                , statsd_parse_field_trim(type, type_end)
                , statsd_parse_field_trim(sampling, sampling_end)
                , statsd_parse_field_trim(tags, tags_end)
        );
    }

    return 0;
}