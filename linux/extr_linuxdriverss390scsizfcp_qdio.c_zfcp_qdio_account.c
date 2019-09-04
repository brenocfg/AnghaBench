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
struct zfcp_qdio {unsigned long long req_q_time; int req_q_util; int /*<<< orphan*/  req_q_free; } ;

/* Variables and functions */
 int QDIO_MAX_BUFFERS_PER_Q ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 unsigned long long get_tod_clock_monotonic () ; 

__attribute__((used)) static inline void zfcp_qdio_account(struct zfcp_qdio *qdio)
{
	unsigned long long now, span;
	int used;

	now = get_tod_clock_monotonic();
	span = (now - qdio->req_q_time) >> 12;
	used = QDIO_MAX_BUFFERS_PER_Q - atomic_read(&qdio->req_q_free);
	qdio->req_q_util += used * span;
	qdio->req_q_time = now;
}