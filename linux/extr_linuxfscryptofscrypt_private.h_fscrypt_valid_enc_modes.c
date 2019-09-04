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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ FS_ENCRYPTION_MODE_AES_128_CBC ; 
 scalar_t__ FS_ENCRYPTION_MODE_AES_128_CTS ; 
 scalar_t__ FS_ENCRYPTION_MODE_AES_256_CTS ; 
 scalar_t__ FS_ENCRYPTION_MODE_AES_256_XTS ; 

__attribute__((used)) static inline bool fscrypt_valid_enc_modes(u32 contents_mode,
					   u32 filenames_mode)
{
	if (contents_mode == FS_ENCRYPTION_MODE_AES_128_CBC &&
	    filenames_mode == FS_ENCRYPTION_MODE_AES_128_CTS)
		return true;

	if (contents_mode == FS_ENCRYPTION_MODE_AES_256_XTS &&
	    filenames_mode == FS_ENCRYPTION_MODE_AES_256_CTS)
		return true;

	return false;
}