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
struct stream {scalar_t__ mime_type; } ;

/* Variables and functions */
 scalar_t__ strcasecmp (scalar_t__,char const* const) ; 

__attribute__((used)) static bool check_mimetype(struct stream *s, const char *const *list)
{
    if (s->mime_type) {
        for (int n = 0; list && list[n]; n++) {
            if (strcasecmp(s->mime_type, list[n]) == 0)
                return true;
        }
    }
    return false;
}