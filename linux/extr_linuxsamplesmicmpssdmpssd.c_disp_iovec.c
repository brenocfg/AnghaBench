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
struct mic_info {int /*<<< orphan*/  name; } ;
struct mic_copy_desc {unsigned int iovcnt; TYPE_1__* iov; } ;
struct TYPE_2__ {int /*<<< orphan*/  iov_len; int /*<<< orphan*/  iov_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  mpsslog (char*,int /*<<< orphan*/ ,char const*,int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
disp_iovec(struct mic_info *mic, struct mic_copy_desc *copy,
	   const char *s, int line)
{
	unsigned int i;

	for (i = 0; i < copy->iovcnt; i++)
		mpsslog("%s %s %d copy->iov[%d] addr %p len 0x%zx\n",
			mic->name, s, line, i,
			copy->iov[i].iov_base, copy->iov[i].iov_len);
}