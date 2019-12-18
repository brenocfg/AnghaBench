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
struct BannerOutput {unsigned int protocol; struct BannerOutput* next; } ;

/* Variables and functions */

__attribute__((used)) static struct BannerOutput *
banout_find_proto(struct BannerOutput *banout, unsigned proto)
{
    while (banout && banout->protocol != proto)
        banout = banout->next;
    return banout;
}