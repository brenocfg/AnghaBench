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
struct BannerOutput {int protocol; scalar_t__ length; } ;

/* Variables and functions */
 struct BannerOutput* banout_find_proto (struct BannerOutput*,unsigned int) ; 

void
banout_end(struct BannerOutput *banout, unsigned proto)
{
    struct BannerOutput *p;

    p = banout_find_proto(banout, proto);
    if (p && p->length) {
        p->protocol |= 0x80000000;
    }
}