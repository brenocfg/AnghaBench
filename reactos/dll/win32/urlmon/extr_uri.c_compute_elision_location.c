#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ ipv4; } ;
typedef  TYPE_1__ ipv6_address ;
typedef  scalar_t__ USHORT ;
typedef  int INT ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */

__attribute__((used)) static void compute_elision_location(const ipv6_address *address, const USHORT values[8],
                                     INT *index, DWORD *count) {
    DWORD i, max_len, cur_len;
    INT max_index, cur_index;

    max_len = cur_len = 0;
    max_index = cur_index = -1;
    for(i = 0; i < 8; ++i) {
        BOOL check_ipv4 = (address->ipv4 && i == 6);
        BOOL is_end = (check_ipv4 || i == 7);

        if(check_ipv4) {
            /* Check if the IPv4 address contains only zeros. */
            if(values[i] == 0 && values[i+1] == 0) {
                if(cur_index == -1)
                    cur_index = i;

                cur_len += 2;
                ++i;
            }
        } else if(values[i] == 0) {
            if(cur_index == -1)
                cur_index = i;

            ++cur_len;
        }

        if(is_end || values[i] != 0) {
            /* We only consider it for an elision if it's
             * more than 1 component long.
             */
            if(cur_len > 1 && cur_len > max_len) {
                /* Found the new elision location. */
                max_len = cur_len;
                max_index = cur_index;
            }

            /* Reset the current range for the next range of zeros. */
            cur_index = -1;
            cur_len = 0;
        }
    }

    *index = max_index;
    *count = max_len;
}