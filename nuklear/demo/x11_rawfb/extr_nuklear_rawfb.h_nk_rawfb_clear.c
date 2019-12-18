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
struct TYPE_2__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct rawfb_context {TYPE_1__ fb; } ;
struct nk_color {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nk_rawfb_fill_rect (struct rawfb_context const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nk_color const) ; 

__attribute__((used)) static void
nk_rawfb_clear(const struct rawfb_context *rawfb, const struct nk_color col)
{
    nk_rawfb_fill_rect(rawfb, 0, 0, rawfb->fb.w, rawfb->fb.h, 0, col);
}