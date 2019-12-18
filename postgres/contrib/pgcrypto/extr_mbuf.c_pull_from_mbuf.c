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
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  PullFilter ;
typedef  int /*<<< orphan*/  MBuf ;

/* Variables and functions */
 int mbuf_grab (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int
pull_from_mbuf(void *arg, PullFilter *src, int len,
			   uint8 **data_p, uint8 *buf, int buflen)
{
	MBuf	   *mbuf = arg;

	return mbuf_grab(mbuf, len, data_p);
}