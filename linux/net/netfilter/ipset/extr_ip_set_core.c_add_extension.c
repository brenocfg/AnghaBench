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
typedef  int u32 ;
struct nlattr {int dummy; } ;
typedef  enum ip_set_ext_id { ____Placeholder_ip_set_ext_id } ip_set_ext_id ;
struct TYPE_2__ {int flag; } ;

/* Variables and functions */
 size_t IPSET_ATTR_TIMEOUT ; 
 TYPE_1__* ip_set_extensions ; 

__attribute__((used)) static inline bool
add_extension(enum ip_set_ext_id id, u32 flags, struct nlattr *tb[])
{
	return ip_set_extensions[id].flag ?
		(flags & ip_set_extensions[id].flag) :
		!!tb[IPSET_ATTR_TIMEOUT];
}