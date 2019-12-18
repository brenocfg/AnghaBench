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
struct mp_image {int dummy; } ;

/* Variables and functions */
 struct mp_image* mp_image_new_ref (struct mp_image*) ; 
 int /*<<< orphan*/  talloc_free (struct mp_image*) ; 

void mp_image_setrefp(struct mp_image **p_img, struct mp_image *new_value)
{
    if (*p_img != new_value) {
        talloc_free(*p_img);
        *p_img = new_value ? mp_image_new_ref(new_value) : NULL;
    }
}