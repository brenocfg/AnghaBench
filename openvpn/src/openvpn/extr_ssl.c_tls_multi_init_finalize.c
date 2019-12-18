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
struct TYPE_2__ {int /*<<< orphan*/  single_session; int /*<<< orphan*/  frame; } ;
struct tls_multi {int /*<<< orphan*/ * session; TYPE_1__ opt; } ;
struct frame {int dummy; } ;

/* Variables and functions */
 size_t TM_ACTIVE ; 
 size_t TM_UNTRUSTED ; 
 int /*<<< orphan*/  tls_init_control_channel_frame_parameters (struct frame const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls_session_init (struct tls_multi*,int /*<<< orphan*/ *) ; 

void
tls_multi_init_finalize(struct tls_multi *multi, const struct frame *frame)
{
    tls_init_control_channel_frame_parameters(frame, &multi->opt.frame);

    /* initialize the active and untrusted sessions */

    tls_session_init(multi, &multi->session[TM_ACTIVE]);

    if (!multi->opt.single_session)
    {
        tls_session_init(multi, &multi->session[TM_UNTRUSTED]);
    }
}