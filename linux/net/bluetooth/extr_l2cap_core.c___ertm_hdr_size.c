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
struct l2cap_chan {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_EXT_CTRL ; 
 unsigned int L2CAP_ENH_HDR_SIZE ; 
 unsigned int L2CAP_EXT_HDR_SIZE ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline unsigned int __ertm_hdr_size(struct l2cap_chan *chan)
{
	if (test_bit(FLAG_EXT_CTRL, &chan->flags))
		return L2CAP_EXT_HDR_SIZE;
	else
		return L2CAP_ENH_HDR_SIZE;
}