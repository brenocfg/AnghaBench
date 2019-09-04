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
struct integrity_iint_cache {int dummy; } ;
struct file {int dummy; } ;
struct evm_ima_xattr_data {int dummy; } ;
typedef  enum ima_hooks { ____Placeholder_ima_hooks } ima_hooks ;

/* Variables and functions */
 int INTEGRITY_UNKNOWN ; 

__attribute__((used)) static inline int ima_appraise_measurement(enum ima_hooks func,
					   struct integrity_iint_cache *iint,
					   struct file *file,
					   const unsigned char *filename,
					   struct evm_ima_xattr_data *xattr_value,
					   int xattr_len)
{
	return INTEGRITY_UNKNOWN;
}