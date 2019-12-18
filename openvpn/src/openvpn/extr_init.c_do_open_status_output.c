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
struct TYPE_4__ {int status_output_owned; scalar_t__ status_output; } ;
struct TYPE_3__ {int /*<<< orphan*/  status_file_update_freq; int /*<<< orphan*/  status_file; } ;
struct context {TYPE_2__ c1; TYPE_1__ options; } ;

/* Variables and functions */
 int /*<<< orphan*/  STATUS_OUTPUT_WRITE ; 
 scalar_t__ status_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
do_open_status_output(struct context *c)
{
    if (!c->c1.status_output)
    {
        c->c1.status_output = status_open(c->options.status_file,
                                          c->options.status_file_update_freq,
                                          -1,
                                          NULL,
                                          STATUS_OUTPUT_WRITE);
        c->c1.status_output_owned = true;
    }
}