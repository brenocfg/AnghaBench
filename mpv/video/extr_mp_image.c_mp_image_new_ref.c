#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mp_image {int num_ff_side_data; TYPE_1__* ff_side_data; int /*<<< orphan*/  a53_cc; int /*<<< orphan*/  icc_profile; int /*<<< orphan*/  hwctx; int /*<<< orphan*/ * bufs; } ;
struct TYPE_3__ {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int MP_MAX_PLANES ; 
 int /*<<< orphan*/  mp_image_destructor ; 
 struct mp_image* mp_image_new_copy (struct mp_image*) ; 
 struct mp_image* new ; 
 int /*<<< orphan*/  ref_buffer (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  talloc_free (struct mp_image*) ; 
 TYPE_1__* talloc_memdup (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 struct mp_image* talloc_ptrtype (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_set_destructor (struct mp_image*,int /*<<< orphan*/ ) ; 

struct mp_image *mp_image_new_ref(struct mp_image *img)
{
    if (!img)
        return NULL;

    if (!img->bufs[0])
        return mp_image_new_copy(img);

    struct mp_image *new = talloc_ptrtype(NULL, new);
    talloc_set_destructor(new, mp_image_destructor);
    *new = *img;

    bool ok = true;
    for (int p = 0; p < MP_MAX_PLANES; p++)
        ref_buffer(&ok, &new->bufs[p]);

    ref_buffer(&ok, &new->hwctx);
    ref_buffer(&ok, &new->icc_profile);
    ref_buffer(&ok, &new->a53_cc);

    new->ff_side_data = talloc_memdup(NULL, new->ff_side_data,
                        new->num_ff_side_data * sizeof(new->ff_side_data[0]));
    for (int n = 0; n < new->num_ff_side_data; n++)
        ref_buffer(&ok, &new->ff_side_data[n].buf);

    if (ok)
        return new;

    // Do this after _all_ bufs were changed; we don't want it to free bufs
    // from the original image if this fails.
    talloc_free(new);
    return NULL;
}