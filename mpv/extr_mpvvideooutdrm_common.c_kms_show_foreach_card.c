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
struct mp_log {int dummy; } ;

/* Variables and functions */
 int DRM_MAX_MINOR ; 
 int /*<<< orphan*/  close (int) ; 
 int open_card (int) ; 

__attribute__((used)) static void kms_show_foreach_card(
    struct mp_log *log, void (*show_fn)(struct mp_log*,int))
{
    for (int card_no = 0; card_no < DRM_MAX_MINOR; card_no++) {
        int fd = open_card(card_no);
        if (fd < 0)
            break;
        close(fd);
        show_fn(log, card_no);
    }
}