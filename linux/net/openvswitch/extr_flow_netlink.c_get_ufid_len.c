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
struct nlattr {int dummy; } ;

/* Variables and functions */
 size_t MAX_UFID_LENGTH ; 
 int /*<<< orphan*/  OVS_NLERR (int,char*,size_t,size_t) ; 
 size_t nla_len (struct nlattr const*) ; 

__attribute__((used)) static size_t get_ufid_len(const struct nlattr *attr, bool log)
{
	size_t len;

	if (!attr)
		return 0;

	len = nla_len(attr);
	if (len < 1 || len > MAX_UFID_LENGTH) {
		OVS_NLERR(log, "ufid size %u bytes exceeds the range (1, %d)",
			  nla_len(attr), MAX_UFID_LENGTH);
		return 0;
	}

	return len;
}