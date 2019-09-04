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
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 scalar_t__ SMB2_OPLOCK_LEVEL_II ; 

__attribute__((used)) static bool
smb2_is_read_op(__u32 oplock)
{
	return oplock == SMB2_OPLOCK_LEVEL_II;
}