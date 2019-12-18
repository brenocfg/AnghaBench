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
struct xdaliclock {int* target_digits; int* current_digits; int /*<<< orphan*/ * gif_enc; int /*<<< orphan*/  frame; void* clear_frame; void* temp_frame; } ;
typedef  int /*<<< orphan*/  ge_GIF ;

/* Variables and functions */
 int /*<<< orphan*/  FRAMES_PER_SECOND ; 
 unsigned int N_ELEMENTS (int*) ; 
 int /*<<< orphan*/  char_height ; 
 int /*<<< orphan*/  char_width ; 
 void* frame_mk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct xdaliclock*) ; 
 struct xdaliclock* malloc (int) ; 

struct xdaliclock *xdaliclock_new(ge_GIF *ge)
{
    struct xdaliclock *xdc = malloc(sizeof(*xdc));

    if (!xdc)
        return NULL;

    xdc->temp_frame = frame_mk(char_width, char_height);
    if (!xdc->temp_frame)
        goto out;

    xdc->clear_frame = frame_mk(char_width, char_height);
    if (!xdc->clear_frame)
        goto out;

    for (unsigned int i = 0; i < N_ELEMENTS(xdc->target_digits); i++)
        xdc->target_digits[i] = xdc->current_digits[i] = -1;

    /* Ensure time() is called the first time xdaliclock_update() is called */
    xdc->frame = FRAMES_PER_SECOND;
    xdc->gif_enc = ge;

    return xdc;

out:
    free(xdc);
    return NULL;
}