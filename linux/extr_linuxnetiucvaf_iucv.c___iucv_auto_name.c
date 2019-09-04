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
struct iucv_sock {int /*<<< orphan*/  src_name; } ;
struct TYPE_2__ {int /*<<< orphan*/  autobind_name; } ;

/* Variables and functions */
 scalar_t__ __iucv_get_sock_by_name (char*) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 TYPE_1__ iucv_sk_list ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static void __iucv_auto_name(struct iucv_sock *iucv)
{
	char name[12];

	sprintf(name, "%08x", atomic_inc_return(&iucv_sk_list.autobind_name));
	while (__iucv_get_sock_by_name(name)) {
		sprintf(name, "%08x",
			atomic_inc_return(&iucv_sk_list.autobind_name));
	}
	memcpy(iucv->src_name, name, 8);
}