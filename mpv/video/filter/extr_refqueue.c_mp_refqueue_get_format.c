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
struct mp_refqueue {struct mp_image* in_format; } ;
struct mp_image {int dummy; } ;

/* Variables and functions */

struct mp_image *mp_refqueue_get_format(struct mp_refqueue *q)
{
    return q->in_format;
}