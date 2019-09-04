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
struct mp_image_params {int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/  imgfmt; } ;
struct mp_image {struct mp_image_params params; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_image_set_size (struct mp_image*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_image_setfmt (struct mp_image*,int /*<<< orphan*/ ) ; 

void mp_image_set_params(struct mp_image *image,
                         const struct mp_image_params *params)
{
    // possibly initialize other stuff
    mp_image_setfmt(image, params->imgfmt);
    mp_image_set_size(image, params->w, params->h);
    image->params = *params;
}