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
typedef  size_t u8 ;
struct gre_protocol {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 size_t GREPROTO_MAX ; 
 int /*<<< orphan*/ * cmpxchg (struct gre_protocol const**,int /*<<< orphan*/ *,struct gre_protocol const*) ; 
 int /*<<< orphan*/ * gre_proto ; 

int gre_add_protocol(const struct gre_protocol *proto, u8 version)
{
	if (version >= GREPROTO_MAX)
		return -EINVAL;

	return (cmpxchg((const struct gre_protocol **)&gre_proto[version], NULL, proto) == NULL) ?
		0 : -EBUSY;
}