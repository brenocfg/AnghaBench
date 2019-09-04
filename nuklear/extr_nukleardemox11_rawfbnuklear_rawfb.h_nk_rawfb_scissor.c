#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct TYPE_4__ {void* h; void* w; void* y; void* x; } ;
struct rawfb_context {TYPE_1__ fb; TYPE_2__ scissors; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX (float const,int /*<<< orphan*/ ) ; 
 void* MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nk_rawfb_scissor(struct rawfb_context *rawfb,
                 const float x,
                 const float y,
                 const float w,
                 const float h)
{
    rawfb->scissors.x = MIN(MAX(x, 0), rawfb->fb.w);
    rawfb->scissors.y = MIN(MAX(y, 0), rawfb->fb.h);
    rawfb->scissors.w = MIN(MAX(w + x, 0), rawfb->fb.w);
    rawfb->scissors.h = MIN(MAX(h + y, 0), rawfb->fb.h);
}