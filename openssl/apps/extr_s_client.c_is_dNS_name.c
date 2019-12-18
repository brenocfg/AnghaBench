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
 size_t strlen (char const*) ; 

__attribute__((used)) static int is_dNS_name(const char *host)
{
    const size_t MAX_LABEL_LENGTH = 63;
    size_t i;
    int isdnsname = 0;
    size_t length = strlen(host);
    size_t label_length = 0;
    int all_numeric = 1;

    /*
     * Deviation from strict DNS name syntax, also check names with '_'
     * Check DNS name syntax, any '-' or '.' must be internal,
     * and on either side of each '.' we can't have a '-' or '.'.
     *
     * If the name has just one label, we don't consider it a DNS name.
     */
    for (i = 0; i < length && label_length < MAX_LABEL_LENGTH; ++i) {
        char c = host[i];

        if ((c >= 'a' && c <= 'z')
            || (c >= 'A' && c <= 'Z')
            || c == '_') {
            label_length += 1;
            all_numeric = 0;
            continue;
        }

        if (c >= '0' && c <= '9') {
            label_length += 1;
            continue;
        }

        /* Dot and hyphen cannot be first or last. */
        if (i > 0 && i < length - 1) {
            if (c == '-') {
                label_length += 1;
                continue;
            }
            /*
             * Next to a dot the preceding and following characters must not be
             * another dot or a hyphen.  Otherwise, record that the name is
             * plausible, since it has two or more labels.
             */
            if (c == '.'
                && host[i + 1] != '.'
                && host[i - 1] != '-'
                && host[i + 1] != '-') {
                label_length = 0;
                isdnsname = 1;
                continue;
            }
        }
        isdnsname = 0;
        break;
    }

    /* dNS name must not be all numeric and labels must be shorter than 64 characters. */
    isdnsname &= !all_numeric && !(label_length == MAX_LABEL_LENGTH);

    return isdnsname;
}