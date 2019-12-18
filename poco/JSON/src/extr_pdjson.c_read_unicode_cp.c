#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int (* get ) (TYPE_2__*) ;} ;
struct TYPE_5__ {TYPE_2__ source; } ;
typedef  TYPE_1__ json_stream ;

/* Variables and functions */
 int EOF ; 
 int hexchar (int) ; 
 int /*<<< orphan*/  json_error (TYPE_1__*,char*,...) ; 
 int stub1 (TYPE_2__*) ; 

__attribute__((used)) static long
read_unicode_cp(json_stream *json)
{
    long cp = 0;
    int shift = 12;

    for (size_t i = 0; i < 4; i++) {
        int c = json->source.get(&json->source);
        int hc;

        if (c == EOF) {
            json_error(json, "%s", "unterminated string literal in unicode");
            return -1;
        } else if ((hc = hexchar(c)) == -1) {
            json_error(json, "bad escape unicode byte, '%c'", c);
            return -1;
        }

        cp += hc * (1 << shift);
        shift -= 4;
    }


    return cp;
}