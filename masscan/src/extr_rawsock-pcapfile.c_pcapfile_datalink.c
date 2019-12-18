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
struct PcapFile {int /*<<< orphan*/  linktype; } ;

/* Variables and functions */

unsigned
pcapfile_datalink(struct PcapFile *handle)
{
    if (handle)
        return (unsigned)handle->linktype;
    else
        return 0;
}