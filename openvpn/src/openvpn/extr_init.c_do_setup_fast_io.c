#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int fast_io; } ;
struct TYPE_4__ {int /*<<< orphan*/  proto; } ;
struct TYPE_5__ {scalar_t__ shaper; TYPE_1__ ce; scalar_t__ fast_io; } ;
struct context {TYPE_3__ c2; TYPE_2__ options; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_INFO ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  proto_is_udp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
do_setup_fast_io(struct context *c)
{
    if (c->options.fast_io)
    {
#ifdef _WIN32
        msg(M_INFO, "NOTE: --fast-io is disabled since we are running on Windows");
#else
        if (!proto_is_udp(c->options.ce.proto))
        {
            msg(M_INFO, "NOTE: --fast-io is disabled since we are not using UDP");
        }
        else
        {
#ifdef ENABLE_FEATURE_SHAPER
            if (c->options.shaper)
            {
                msg(M_INFO, "NOTE: --fast-io is disabled since we are using --shaper");
            }
            else
#endif
            {
                c->c2.fast_io = true;
            }
        }
#endif
    }
}