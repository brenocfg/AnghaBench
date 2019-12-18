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
struct l2cap_chan {int dummy; } ;

/* Variables and functions */
 long L2CAP_CONN_TIMEOUT ; 

__attribute__((used)) static long chan_get_sndtimeo_cb(struct l2cap_chan *chan)
{
	return L2CAP_CONN_TIMEOUT;
}