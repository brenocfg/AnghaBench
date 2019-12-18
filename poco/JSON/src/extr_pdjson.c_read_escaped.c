#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int (* get ) (TYPE_2__*) ;} ;
struct TYPE_7__ {TYPE_2__ source; } ;
typedef  TYPE_1__ json_stream ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  json_error (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  pushchar (TYPE_1__*,char) ; 
 scalar_t__ read_unicode (TYPE_1__*) ; 
 scalar_t__ strchr (char const*,int) ; 
 int stub1 (TYPE_2__*) ; 

int read_escaped(json_stream *json)
{
    int c = json->source.get(&json->source);
    if (c == EOF) {
        json_error(json, "%s", "unterminated string literal in escape");
        return -1;
    } else if (c == 'u') {
        if (read_unicode(json) != 0)
            return -1;
    } else {
        switch (c) {
        case '\\':
        case 'b':
        case 'f':
        case 'n':
        case 'r':
        case 't':
        case '/':
        case '"':
            {
                const char *codes = "\\bfnrt/\"";
                char *p = (char*) strchr(codes, c);
                if (pushchar(json, "\\\b\f\n\r\t/\""[p - codes]) != 0)
                    return -1;
            }
            break;
        default:
            json_error(json, "bad escaped byte, '%c'", c);
            return -1;
        }
    }
    return 0;
}