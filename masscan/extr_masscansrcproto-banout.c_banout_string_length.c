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
struct BannerOutput {unsigned int protocol; int length; struct BannerOutput* next; } ;

/* Variables and functions */

unsigned
banout_string_length(const struct BannerOutput *banout, unsigned proto)
{
    while (banout && banout->protocol != proto)
        banout = banout->next;

    if (banout)
        return banout->length;
    else
        return 0;
}