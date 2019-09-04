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
struct policydb {int dummy; } ;
struct netlbl_lsm_secattr {int dummy; } ;
struct context {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 

__attribute__((used)) static inline int mls_export_netlbl_cat(struct policydb *p,
					struct context *context,
					struct netlbl_lsm_secattr *secattr)
{
	return -ENOMEM;
}