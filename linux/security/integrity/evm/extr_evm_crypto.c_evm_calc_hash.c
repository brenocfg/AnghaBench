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
struct evm_digest {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int evm_calc_hmac_or_hash (struct dentry*,char const*,char const*,size_t,char,struct evm_digest*) ; 

int evm_calc_hash(struct dentry *dentry, const char *req_xattr_name,
		  const char *req_xattr_value, size_t req_xattr_value_len,
		  char type, struct evm_digest *data)
{
	return evm_calc_hmac_or_hash(dentry, req_xattr_name, req_xattr_value,
				     req_xattr_value_len, type, data);
}