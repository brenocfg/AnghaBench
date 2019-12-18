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
 scalar_t__ strstr (char*,char*) ; 

inline int url_is_request_complete(char *begin, char *end, size_t length) {

    if ( begin == end) {
        //Message cannot be complete when first and last address are the same
        return 0;
    }

    //This math to verify  the last is valid, because we are discarding the POST
    if (length > 4) {
        begin = end - 4;
    }

    return (strstr(begin, "\r\n\r\n"))?1:0;
}