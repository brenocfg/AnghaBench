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
struct tcp_sock {scalar_t__ snd_una; scalar_t__ snd_up; } ;

/* Variables and functions */

__attribute__((used)) static inline bool tcp_urg_mode(const struct tcp_sock *tp)
{
	return tp->snd_una != tp->snd_up;
}