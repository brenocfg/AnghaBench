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
struct tl_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_file_seg (struct tl_ctx*,char*,int) ; 

__attribute__((used)) static void check_file(struct tl_ctx *ctx, char *filename, int first)
{
    for (int segment = first; ; segment++) {
        if (!check_file_seg(ctx, filename, segment))
            break;
    }
}