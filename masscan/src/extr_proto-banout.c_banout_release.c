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
struct BannerOutput {struct BannerOutput* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  banout_init (struct BannerOutput*) ; 
 int /*<<< orphan*/  free (struct BannerOutput*) ; 

void
banout_release(struct BannerOutput *banout)
{
    while (banout->next) {
        struct BannerOutput *next = banout->next->next;
        free(banout->next);
        banout->next = next;
    }
    banout_init(banout);
}