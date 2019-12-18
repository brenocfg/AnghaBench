#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct echoaudio {TYPE_2__* comm_page; } ;
struct TYPE_6__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  area; } ;
struct audiopipe {size_t index; TYPE_3__ sgpage; scalar_t__ sglist_head; } ;
struct TYPE_5__ {TYPE_1__* sglist_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sglist_init(struct echoaudio *chip, struct audiopipe *pipe)
{
	pipe->sglist_head = 0;
	memset(pipe->sgpage.area, 0, PAGE_SIZE);
	chip->comm_page->sglist_addr[pipe->index].addr =
		cpu_to_le32(pipe->sgpage.addr);
	return 0;
}