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
struct aifs_status {int streams; } ;

/* Variables and functions */

__attribute__((used)) static bool aif_active(struct aifs_status *status, int aif_id)
{
	return (0x03 << aif_id * 2) & status->streams;
}