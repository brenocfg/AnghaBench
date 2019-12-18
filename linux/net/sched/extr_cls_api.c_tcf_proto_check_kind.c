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
 scalar_t__ IFNAMSIZ ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ nla_strlcpy (char*,struct nlattr*,scalar_t__) ; 

__attribute__((used)) static bool tcf_proto_check_kind(struct nlattr *kind, char *name)
{
	if (kind)
		return nla_strlcpy(name, kind, IFNAMSIZ) >= IFNAMSIZ;
	memset(name, 0, IFNAMSIZ);
	return false;
}