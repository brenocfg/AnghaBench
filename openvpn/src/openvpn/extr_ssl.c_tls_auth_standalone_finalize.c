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
struct tls_auth_standalone {int /*<<< orphan*/  frame; } ;
struct frame {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tls_init_control_channel_frame_parameters (struct frame const*,int /*<<< orphan*/ *) ; 

void
tls_auth_standalone_finalize(struct tls_auth_standalone *tas,
                             const struct frame *frame)
{
    tls_init_control_channel_frame_parameters(frame, &tas->frame);
}