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
struct tun_security_struct {int /*<<< orphan*/  sid; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  current_sid () ; 
 struct tun_security_struct* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int selinux_tun_dev_alloc_security(void **security)
{
	struct tun_security_struct *tunsec;

	tunsec = kzalloc(sizeof(*tunsec), GFP_KERNEL);
	if (!tunsec)
		return -ENOMEM;
	tunsec->sid = current_sid();

	*security = tunsec;
	return 0;
}