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
struct vo {int dummy; } ;
struct sub_bitmaps {int /*<<< orphan*/  render_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  draw_osd_part (struct vo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generate_osd_part (struct vo*,struct sub_bitmaps*) ; 

__attribute__((used)) static void draw_osd_cb(void *ctx, struct sub_bitmaps *imgs)
{
    struct vo *vo = ctx;
    generate_osd_part(vo, imgs);
    draw_osd_part(vo, imgs->render_index);
}