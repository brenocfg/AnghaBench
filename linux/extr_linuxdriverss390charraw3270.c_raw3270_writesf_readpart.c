#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wbuf ;
struct TYPE_6__ {int count; scalar_t__ cda; int /*<<< orphan*/  flags; int /*<<< orphan*/  cmd_code; } ;
struct TYPE_7__ {TYPE_1__ ccw; } ;
struct raw3270 {TYPE_2__ init_readpart; int /*<<< orphan*/  init_view; int /*<<< orphan*/  state; TYPE_2__ init_data; } ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  CCW_FLAG_SLI ; 
 int /*<<< orphan*/  RAW3270_STATE_W4ATTN ; 
 int /*<<< orphan*/  TC_WRITESF ; 
 scalar_t__ __pa (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,unsigned char const*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  raw3270_start_irq (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static void
raw3270_writesf_readpart(struct raw3270 *rp)
{
	static const unsigned char wbuf[] =
		{ 0x00, 0x07, 0x01, 0xff, 0x03, 0x00, 0x81 };

	/* Store 'read partition' data stream to init_data */
	memset(&rp->init_readpart, 0, sizeof(rp->init_readpart));
	memset(&rp->init_data, 0, sizeof(rp->init_data));
	memcpy(&rp->init_data, wbuf, sizeof(wbuf));
	rp->init_readpart.ccw.cmd_code = TC_WRITESF;
	rp->init_readpart.ccw.flags = CCW_FLAG_SLI;
	rp->init_readpart.ccw.count = sizeof(wbuf);
	rp->init_readpart.ccw.cda = (__u32) __pa(&rp->init_data);
	rp->state = RAW3270_STATE_W4ATTN;
	raw3270_start_irq(&rp->init_view, &rp->init_readpart);
}