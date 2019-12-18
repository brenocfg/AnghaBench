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

/* Variables and functions */
 int /*<<< orphan*/  OPENVPN_AEAD_TAG_LENGTH ; 
 unsigned int OPENVPN_MAX_CIPHER_BLOCK_SIZE ; 
 int /*<<< orphan*/  OPENVPN_MAX_HMAC_SIZE ; 
 unsigned int OPENVPN_MAX_IV_LENGTH ; 
 unsigned int max_int (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int packet_id_size (int) ; 

unsigned int
crypto_max_overhead(void)
{
    return packet_id_size(true) + OPENVPN_MAX_IV_LENGTH
           +OPENVPN_MAX_CIPHER_BLOCK_SIZE
           +max_int(OPENVPN_MAX_HMAC_SIZE, OPENVPN_AEAD_TAG_LENGTH);
}