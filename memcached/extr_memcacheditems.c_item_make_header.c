#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  item ;
typedef  int /*<<< orphan*/  flags ;
struct TYPE_2__ {scalar_t__ inline_ascii_response; } ;

/* Variables and functions */
 TYPE_1__ settings ; 
 scalar_t__ snprintf (char*,int,char*,unsigned int const,int const) ; 

__attribute__((used)) static size_t item_make_header(const uint8_t nkey, const unsigned int flags, const int nbytes,
                     char *suffix, uint8_t *nsuffix) {
    if (settings.inline_ascii_response) {
        /* suffix is defined at 40 chars elsewhere.. */
        *nsuffix = (uint8_t) snprintf(suffix, 40, " %u %d\r\n", flags, nbytes - 2);
    } else {
        if (flags == 0) {
            *nsuffix = 0;
        } else {
            *nsuffix = sizeof(flags);
        }
    }
    return sizeof(item) + nkey + *nsuffix + nbytes;
}