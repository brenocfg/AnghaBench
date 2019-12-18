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
struct user_namespace {int dummy; } ;
struct idmap {TYPE_1__* cred; } ;
struct TYPE_2__ {struct user_namespace* user_ns; } ;

/* Variables and functions */
 struct user_namespace init_user_ns ; 

__attribute__((used)) static struct user_namespace *idmap_userns(const struct idmap *idmap)
{
	if (idmap && idmap->cred)
		return idmap->cred->user_ns;
	return &init_user_ns;
}