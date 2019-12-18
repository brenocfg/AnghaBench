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
struct fscrypt_key_specifier {scalar_t__ __reserved; } ;

/* Variables and functions */
 scalar_t__ master_key_spec_len (struct fscrypt_key_specifier const*) ; 

__attribute__((used)) static inline bool valid_key_spec(const struct fscrypt_key_specifier *spec)
{
	if (spec->__reserved)
		return false;
	return master_key_spec_len(spec) != 0;
}