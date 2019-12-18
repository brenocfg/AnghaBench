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
struct rrdengine_instance {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RRDENG_MIN_DISK_SPACE_MB ; 
 int /*<<< orphan*/  RRDENG_MIN_PAGE_CACHE_SIZE_MB ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rrdeng_exit (struct rrdengine_instance*) ; 
 int rrdeng_init (struct rrdengine_instance**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

void rrdengine_main(void)
{
    int ret;
    struct rrdengine_instance *ctx;

    ret = rrdeng_init(&ctx, "/tmp", RRDENG_MIN_PAGE_CACHE_SIZE_MB, RRDENG_MIN_DISK_SPACE_MB);
    if (ret) {
        exit(ret);
    }
    rrdeng_exit(ctx);
    fprintf(stderr, "Hello world!");
    exit(0);
}