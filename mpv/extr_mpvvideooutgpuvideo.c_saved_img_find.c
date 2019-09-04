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
struct image {int dummy; } ;
struct gl_video {int num_saved_imgs; TYPE_1__* saved_imgs; } ;
struct TYPE_2__ {struct image img; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static bool saved_img_find(struct gl_video *p, const char *name,
                           struct image *out)
{
    if (!name || !out)
        return false;

    for (int i = 0; i < p->num_saved_imgs; i++) {
        if (strcmp(p->saved_imgs[i].name, name) == 0) {
            *out = p->saved_imgs[i].img;
            return true;
        }
    }

    return false;
}