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
struct atio {scalar_t__ entry_type; int /*<<< orphan*/  attr_n_length; } ;

/* Variables and functions */
 scalar_t__ ATIO_TYPE7 ; 
 int FCP_CMD_LENGTH_MASK ; 
 int FCP_CMD_LENGTH_MIN ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int fcpcmd_is_corrupted(struct atio *atio)
{
	if (atio->entry_type == ATIO_TYPE7 &&
	    ((le16_to_cpu(atio->attr_n_length) & FCP_CMD_LENGTH_MASK) <
	     FCP_CMD_LENGTH_MIN))
		return 1;
	else
		return 0;
}