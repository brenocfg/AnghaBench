#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int (* get ) (TYPE_2__*) ;} ;
struct TYPE_8__ {TYPE_2__ source; } ;
typedef  TYPE_1__ json_stream ;

/* Variables and functions */
 int EOF ; 
 int encode_utf8 (TYPE_1__*,long) ; 
 int /*<<< orphan*/  json_error (TYPE_1__*,char*,...) ; 
 long read_unicode_cp (TYPE_1__*) ; 
 int stub1 (TYPE_2__*) ; 
 int stub2 (TYPE_2__*) ; 

__attribute__((used)) static int read_unicode(json_stream *json)
{
    long cp, h, l;

    if ((cp = read_unicode_cp(json)) == -1) {
        return -1;
    }

    if (cp >= 0xd800 && cp <= 0xdbff) {
        /* This is the high portion of a surrogate pair; we need to read the
         * lower portion to get the codepoint
         */
        h = cp;

        int c = json->source.get(&json->source);
        if (c == EOF) {
            json_error(json, "%s", "unterminated string literal in unicode");
            return -1;
        } else if (c != '\\') {
            json_error(json, "invalid continuation for surrogate pair: '%c', "
                             "expected '\\'", c);
            return -1;
        }

        c = json->source.get(&json->source);
        if (c == EOF) {
            json_error(json, "%s", "unterminated string literal in unicode");
            return -1;
        } else if (c != 'u') {
            json_error(json, "invalid continuation for surrogate pair: '%c', "
                             "expected 'u'", c);
            return -1;
        }

        if ((l = read_unicode_cp(json)) == -1) {
            return -1;
        }

        if (l < 0xdc00 || l > 0xdfff) {
            json_error(json, "invalid surrogate pair continuation \\u%04lx out "
                             "of range (dc00-dfff)", l);
            return -1;
        }

        cp = ((h - 0xd800) * 0x400) + ((l - 0xdc00) + 0x10000);
    } else if (cp >= 0xdc00 && cp <= 0xdfff) {
            json_error(json, "dangling surrogate \\u%04lx", cp);
            return -1;
    }

    return encode_utf8(json, cp);
}