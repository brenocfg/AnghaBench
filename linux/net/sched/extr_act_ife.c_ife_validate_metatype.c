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
struct tcf_meta_ops {int (* validate ) (void*,int) ;scalar_t__ metatype; } ;

/* Variables and functions */
 scalar_t__ NLA_U16 ; 
 scalar_t__ NLA_U32 ; 
 int ife_validate_meta_u16 (void*,int) ; 
 int ife_validate_meta_u32 (void*,int) ; 
 int stub1 (void*,int) ; 

__attribute__((used)) static int ife_validate_metatype(struct tcf_meta_ops *ops, void *val, int len)
{
	int ret = 0;
	/* XXX: unfortunately cant use nla_policy at this point
	* because a length of 0 is valid in the case of
	* "allow". "use" semantics do enforce for proper
	* length and i couldve use nla_policy but it makes it hard
	* to use it just for that..
	*/
	if (ops->validate)
		return ops->validate(val, len);

	if (ops->metatype == NLA_U32)
		ret = ife_validate_meta_u32(val, len);
	else if (ops->metatype == NLA_U16)
		ret = ife_validate_meta_u16(val, len);

	return ret;
}