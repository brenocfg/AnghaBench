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
struct niu {int num_ldg; TYPE_1__* ldg; } ;
struct TYPE_2__ {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void niu_disable_napi(struct niu *np)
{
	int i;

	for (i = 0; i < np->num_ldg; i++)
		napi_disable(&np->ldg[i].napi);
}