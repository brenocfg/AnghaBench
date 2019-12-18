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
struct TYPE_2__ {scalar_t__ residual_fully_formed; } ;
struct link_socket {TYPE_1__ stream_buf; } ;

/* Variables and functions */

__attribute__((used)) static inline bool
socket_read_residual(const struct link_socket *s)
{
    return s && s->stream_buf.residual_fully_formed;
}