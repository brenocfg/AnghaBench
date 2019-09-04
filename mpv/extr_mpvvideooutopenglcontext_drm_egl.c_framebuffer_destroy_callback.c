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
struct gbm_bo {int dummy; } ;
struct framebuffer {int /*<<< orphan*/  id; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  drmModeRmFB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void framebuffer_destroy_callback(struct gbm_bo *bo, void *data)
{
    struct framebuffer *fb = data;
    if (fb) {
        drmModeRmFB(fb->fd, fb->id);
    }
}