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
struct stream {int /*<<< orphan*/  cancel; } ;

/* Variables and functions */
 int mp_cancel_test (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int interrupt_cb(void *ctx)
{
    struct stream *stream = ctx;
    return mp_cancel_test(stream->cancel);
}