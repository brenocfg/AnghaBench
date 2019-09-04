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
struct priv {int pflip_happening; } ;

/* Variables and functions */

__attribute__((used)) static void page_flipped(int fd, unsigned int frame, unsigned int sec,
                         unsigned int usec, void *data)
{
    struct priv *p = data;
    p->pflip_happening = false;
}