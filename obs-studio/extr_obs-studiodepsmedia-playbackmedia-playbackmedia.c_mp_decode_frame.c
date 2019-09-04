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
struct mp_decode {scalar_t__ frame_ready; } ;

/* Variables and functions */
 scalar_t__ mp_decode_next (struct mp_decode*) ; 

__attribute__((used)) static inline bool mp_decode_frame(struct mp_decode *d)
{
	return d->frame_ready || mp_decode_next(d);
}