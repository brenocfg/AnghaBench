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
typedef  scalar_t__ uint32_t ;
struct units_formatter {char const* units; scalar_t__ hash; scalar_t__ format; } ;
typedef  double calculated_number ;
typedef  scalar_t__ UNITS_FORMAT ;

/* Variables and functions */
 scalar_t__ UNITS_FORMAT_EMPTY ; 
 scalar_t__ UNITS_FORMAT_HOURS ; 
 scalar_t__ UNITS_FORMAT_HOURS_AGO ; 
 scalar_t__ UNITS_FORMAT_MINUTES ; 
 scalar_t__ UNITS_FORMAT_MINUTES_AGO ; 
 scalar_t__ UNITS_FORMAT_NONE ; 
 scalar_t__ UNITS_FORMAT_OKERROR ; 
 scalar_t__ UNITS_FORMAT_OKFAILED ; 
 scalar_t__ UNITS_FORMAT_ONOFF ; 
 scalar_t__ UNITS_FORMAT_PERCENT ; 
 scalar_t__ UNITS_FORMAT_SECONDS ; 
 scalar_t__ UNITS_FORMAT_SECONDS_AGO ; 
 scalar_t__ UNITS_FORMAT_UPDOWN ; 
 struct units_formatter* badge_units_formatters ; 
 char* format_value_with_precision_and_unit (char*,size_t,double,char const*,int) ; 
 scalar_t__ isinf (double) ; 
 scalar_t__ isnan (double) ; 
 void* simple_hash (char const*) ; 
 int /*<<< orphan*/  snprintfz (char*,size_t,char*,...) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ unlikely (int) ; 

inline char *format_value_and_unit(char *value_string, size_t value_string_len, calculated_number value, const char *units, int precision) {
    static int max = -1;
    int i;

    if(unlikely(max == -1)) {
        for(i = 0; badge_units_formatters[i].units; i++)
            badge_units_formatters[i].hash = simple_hash(badge_units_formatters[i].units);

        max = i;
    }

    if(unlikely(!units)) units = "";
    uint32_t hash_units = simple_hash(units);

    UNITS_FORMAT format = UNITS_FORMAT_NONE;
    for(i = 0; i < max; i++) {
        struct units_formatter *ptr = &badge_units_formatters[i];

        if(hash_units == ptr->hash && !strcmp(units, ptr->units)) {
            format = ptr->format;
            break;
        }
    }

    if(unlikely(format == UNITS_FORMAT_SECONDS || format == UNITS_FORMAT_SECONDS_AGO)) {
        if(value == 0.0) {
            snprintfz(value_string, value_string_len, "%s", "now");
            return value_string;
        }
        else if(isnan(value) || isinf(value)) {
            snprintfz(value_string, value_string_len, "%s", "undefined");
            return value_string;
        }

        const char *suffix = (format == UNITS_FORMAT_SECONDS_AGO)?" ago":"";

        size_t s = (size_t)value;
        size_t d = s / 86400;
        s = s % 86400;

        size_t h = s / 3600;
        s = s % 3600;

        size_t m = s / 60;
        s = s % 60;

        if(d)
            snprintfz(value_string, value_string_len, "%zu %s %02zu:%02zu:%02zu%s", d, (d == 1)?"day":"days", h, m, s, suffix);
        else
            snprintfz(value_string, value_string_len, "%02zu:%02zu:%02zu%s", h, m, s, suffix);

        return value_string;
    }

    else if(unlikely(format == UNITS_FORMAT_MINUTES || format == UNITS_FORMAT_MINUTES_AGO)) {
        if(value == 0.0) {
            snprintfz(value_string, value_string_len, "%s", "now");
            return value_string;
        }
        else if(isnan(value) || isinf(value)) {
            snprintfz(value_string, value_string_len, "%s", "undefined");
            return value_string;
        }

        const char *suffix = (format == UNITS_FORMAT_MINUTES_AGO)?" ago":"";

        size_t m = (size_t)value;
        size_t d = m / (60 * 24);
        m = m % (60 * 24);

        size_t h = m / 60;
        m = m % 60;

        if(d)
            snprintfz(value_string, value_string_len, "%zud %02zuh %02zum%s", d, h, m, suffix);
        else
            snprintfz(value_string, value_string_len, "%zuh %zum%s", h, m, suffix);

        return value_string;
    }

    else if(unlikely(format == UNITS_FORMAT_HOURS || format == UNITS_FORMAT_HOURS_AGO)) {
        if(value == 0.0) {
            snprintfz(value_string, value_string_len, "%s", "now");
            return value_string;
        }
        else if(isnan(value) || isinf(value)) {
            snprintfz(value_string, value_string_len, "%s", "undefined");
            return value_string;
        }

        const char *suffix = (format == UNITS_FORMAT_HOURS_AGO)?" ago":"";

        size_t h = (size_t)value;
        size_t d = h / 24;
        h = h % 24;

        if(d)
            snprintfz(value_string, value_string_len, "%zud %zuh%s", d, h, suffix);
        else
            snprintfz(value_string, value_string_len, "%zuh%s", h, suffix);

        return value_string;
    }

    else if(unlikely(format == UNITS_FORMAT_ONOFF)) {
        snprintfz(value_string, value_string_len, "%s", (value != 0.0)?"on":"off");
        return value_string;
    }

    else if(unlikely(format == UNITS_FORMAT_UPDOWN)) {
        snprintfz(value_string, value_string_len, "%s", (value != 0.0)?"up":"down");
        return value_string;
    }

    else if(unlikely(format == UNITS_FORMAT_OKERROR)) {
        snprintfz(value_string, value_string_len, "%s", (value != 0.0)?"ok":"error");
        return value_string;
    }

    else if(unlikely(format == UNITS_FORMAT_OKFAILED)) {
        snprintfz(value_string, value_string_len, "%s", (value != 0.0)?"ok":"failed");
        return value_string;
    }

    else if(unlikely(format == UNITS_FORMAT_EMPTY))
        units = "";

    else if(unlikely(format == UNITS_FORMAT_PERCENT))
        units = "%";

    if(unlikely(isnan(value) || isinf(value))) {
        strcpy(value_string, "-");
        return value_string;
    }

    return format_value_with_precision_and_unit(value_string, value_string_len, value, units, precision);
}