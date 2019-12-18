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
struct mp_vdpau_mixer_frame {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  talloc_free (struct mp_vdpau_mixer_frame*) ; 

__attribute__((used)) static void free_mixed_frame(void *arg)
{
    struct mp_vdpau_mixer_frame *frame = arg;
    talloc_free(frame);
}