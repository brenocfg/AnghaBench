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
struct darray {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * annexb_startcode ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  packet_put (struct darray*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void packet_put_startcode(struct darray *packet, int size)
{
	assert(size == 3 || size == 4);

	packet_put(packet, &annexb_startcode[4 - size], size);
}