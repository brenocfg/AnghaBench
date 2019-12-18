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
typedef  int /*<<< orphan*/  AVBufferRef ;

/* Variables and functions */
 int /*<<< orphan*/  MP_HANDLE_OOM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * av_buffer_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ **) ; 

__attribute__((used)) static void assign_bufref(AVBufferRef **dst, AVBufferRef *new)
{
    av_buffer_unref(dst);
    if (new) {
        *dst = av_buffer_ref(new);
        MP_HANDLE_OOM(*dst);
    }
}