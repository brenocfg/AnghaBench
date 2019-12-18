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
typedef  int uint64 ;
typedef  scalar_t__ uint32 ;
typedef  int /*<<< orphan*/  dsm_control_item ;

/* Variables and functions */
 int /*<<< orphan*/  dsm_control_header ; 
 int /*<<< orphan*/  item ; 
 int offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64
dsm_control_bytes_needed(uint32 nitems)
{
	return offsetof(dsm_control_header, item)
		+ sizeof(dsm_control_item) * (uint64) nitems;
}