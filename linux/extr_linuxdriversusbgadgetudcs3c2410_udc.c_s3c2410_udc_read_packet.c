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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {scalar_t__ actual; scalar_t__ length; } ;
struct s3c2410_request {TYPE_1__ req; } ;

/* Variables and functions */
 scalar_t__ base_addr ; 
 unsigned int min (scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  readsb (scalar_t__,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static inline int s3c2410_udc_read_packet(int fifo, u8 *buf,
		struct s3c2410_request *req, unsigned avail)
{
	unsigned len;

	len = min(req->req.length - req->req.actual, avail);
	req->req.actual += len;

	readsb(fifo + base_addr, buf, len);
	return len;
}