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
struct fscrypt_key_specifier {int type; } ;

/* Variables and functions */
 int FSCRYPT_KEY_DESCRIPTOR_SIZE ; 
 int FSCRYPT_KEY_IDENTIFIER_SIZE ; 
#define  FSCRYPT_KEY_SPEC_TYPE_DESCRIPTOR 129 
#define  FSCRYPT_KEY_SPEC_TYPE_IDENTIFIER 128 

__attribute__((used)) static inline int master_key_spec_len(const struct fscrypt_key_specifier *spec)
{
	switch (spec->type) {
	case FSCRYPT_KEY_SPEC_TYPE_DESCRIPTOR:
		return FSCRYPT_KEY_DESCRIPTOR_SIZE;
	case FSCRYPT_KEY_SPEC_TYPE_IDENTIFIER:
		return FSCRYPT_KEY_IDENTIFIER_SIZE;
	}
	return 0;
}