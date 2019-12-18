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
struct vo {struct priv* priv; } ;
struct priv {int /*<<< orphan*/  frame; int /*<<< orphan*/  sws; } ;
struct mp_image {int dummy; } ;
typedef  struct mp_image mp_image_t ;

/* Variables and functions */
 int /*<<< orphan*/  mp_sws_scale (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mp_image*) ; 
 int /*<<< orphan*/  talloc_free (struct mp_image*) ; 

__attribute__((used)) static void draw_image(struct vo *vo, mp_image_t *mpi)
{
    struct priv *p = vo->priv;
    struct mp_image src = *mpi;
    // XXX: pan, crop etc.
    mp_sws_scale(p->sws, p->frame, &src);
    talloc_free(mpi);
}