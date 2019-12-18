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
struct modsig {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;
typedef  enum ima_hooks { ____Placeholder_ima_hooks } ima_hooks ;

/* Variables and functions */
 int EOPNOTSUPP ; 

__attribute__((used)) static inline int ima_read_modsig(enum ima_hooks func, const void *buf,
				  loff_t buf_len, struct modsig **modsig)
{
	return -EOPNOTSUPP;
}