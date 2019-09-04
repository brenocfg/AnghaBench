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
struct timespec64 {int tv_nsec; int tv_sec; } ;
struct ravb_private {struct net_device* ndev; } ;
struct net_device {int dummy; } ;
typedef  int s64 ;

/* Variables and functions */
 int /*<<< orphan*/  GCCR_TCR_CAPTURE ; 
 int /*<<< orphan*/  GCT0 ; 
 int /*<<< orphan*/  GCT1 ; 
 int /*<<< orphan*/  GCT2 ; 
 int ravb_ptp_tcr_request (struct ravb_private*,int /*<<< orphan*/ ) ; 
 int ravb_read (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ravb_ptp_time_read(struct ravb_private *priv, struct timespec64 *ts)
{
	struct net_device *ndev = priv->ndev;
	int error;

	error = ravb_ptp_tcr_request(priv, GCCR_TCR_CAPTURE);
	if (error)
		return error;

	ts->tv_nsec = ravb_read(ndev, GCT0);
	ts->tv_sec  = ravb_read(ndev, GCT1) |
		((s64)ravb_read(ndev, GCT2) << 32);

	return 0;
}