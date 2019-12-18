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
typedef  int /*<<< orphan*/  uint8_t ;
struct darray {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  darray_push_back_array (int,struct darray*,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static void packet_put(struct darray *packet, const uint8_t *buf, size_t size)
{
	darray_push_back_array(sizeof(uint8_t), packet, buf, size);
}