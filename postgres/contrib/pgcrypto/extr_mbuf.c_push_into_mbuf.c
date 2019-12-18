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
typedef  int /*<<< orphan*/  PushFilter ;
typedef  int /*<<< orphan*/  MBuf ;

/* Variables and functions */
 int mbuf_append (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int
push_into_mbuf(PushFilter *next, void *arg, const uint8 *data, int len)
{
	int			res = 0;
	MBuf	   *mbuf = arg;

	if (len > 0)
		res = mbuf_append(mbuf, data, len);
	return res < 0 ? res : 0;
}