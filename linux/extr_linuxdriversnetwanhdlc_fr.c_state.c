#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct frad_state {int dummy; } ;
struct TYPE_3__ {scalar_t__ state; } ;
typedef  TYPE_1__ hdlc_device ;

/* Variables and functions */

__attribute__((used)) static inline struct frad_state* state(hdlc_device *hdlc)
{
	return(struct frad_state *)(hdlc->state);
}