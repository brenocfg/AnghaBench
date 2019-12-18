#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
struct TYPE_4__ {int data_end; scalar_t__ no_write; } ;
typedef  TYPE_1__ MBuf ;

/* Variables and functions */
 int PXE_BUG ; 
 int /*<<< orphan*/  memcpy (int,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  prepare_room (TYPE_1__*,int) ; 
 int /*<<< orphan*/  px_debug (char*) ; 

int
mbuf_append(MBuf *dst, const uint8 *buf, int len)
{
	if (dst->no_write)
	{
		px_debug("mbuf_append: no_write");
		return PXE_BUG;
	}

	prepare_room(dst, len);

	memcpy(dst->data_end, buf, len);
	dst->data_end += len;

	return 0;
}