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
typedef  int /*<<< orphan*/  cbc_handles ;

/* Variables and functions */
 size_t AES_CBC_128 ; 
 size_t AES_CBC_192 ; 
 size_t AES_CBC_256 ; 
#define  NID_aes_128_cbc 130 
#define  NID_aes_192_cbc 129 
#define  NID_aes_256_cbc 128 
 int /*<<< orphan*/ * cbc_handle ; 

__attribute__((used)) static cbc_handles *get_cipher_handle(int nid)
{
    switch (nid) {
    case NID_aes_128_cbc:
        return &cbc_handle[AES_CBC_128];
    case NID_aes_192_cbc:
        return &cbc_handle[AES_CBC_192];
    case NID_aes_256_cbc:
        return &cbc_handle[AES_CBC_256];
    default:
        return NULL;
    }
}