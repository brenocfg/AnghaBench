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
struct nfs42_layouterror_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfs42_free_layouterror_data (struct nfs42_layouterror_data*) ; 

__attribute__((used)) static void
nfs42_layouterror_release(void *calldata)
{
	struct nfs42_layouterror_data *data = calldata;

	nfs42_free_layouterror_data(data);
}