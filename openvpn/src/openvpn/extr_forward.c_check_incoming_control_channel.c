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
struct TYPE_2__ {int /*<<< orphan*/  tls_multi; } ;
struct context {TYPE_1__ c2; } ;

/* Variables and functions */
 scalar_t__ tls_test_payload_len (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
check_incoming_control_channel(struct context *c)
{
#if P2MP
    void check_incoming_control_channel_dowork(struct context *c);

    if (tls_test_payload_len(c->c2.tls_multi) > 0)
    {
        check_incoming_control_channel_dowork(c);
    }
#endif
}