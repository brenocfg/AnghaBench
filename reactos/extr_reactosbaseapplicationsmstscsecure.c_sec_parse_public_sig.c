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
typedef  int /*<<< orphan*/  uint8 ;
typedef  int uint32 ;
typedef  int /*<<< orphan*/  signature ;
typedef  int /*<<< orphan*/  STREAM ;
typedef  int /*<<< orphan*/  RD_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_RDP5 (char*) ; 
 int /*<<< orphan*/  SEC_EXPONENT_SIZE ; 
 int SEC_MAX_MODULUS_SIZE ; 
 int /*<<< orphan*/  SEC_MODULUS_SIZE ; 
 int /*<<< orphan*/  True ; 
 int /*<<< orphan*/  g_server_public_key_len ; 
 scalar_t__ g_testkey ; 
 int /*<<< orphan*/  in_uint8a (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ rdssl_sign_ok (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int,char*) ; 
 int /*<<< orphan*/  s_check (int /*<<< orphan*/ ) ; 

__attribute__((used)) static RD_BOOL
sec_parse_public_sig(STREAM s, uint32 len, uint8 * modulus, uint8 * exponent)
{
	uint8 signature[SEC_MAX_MODULUS_SIZE];
	uint8 signature_[SEC_MAX_MODULUS_SIZE];
	uint32 sig_len;

	if (len != 72)
	{
		return True;
	}
	memset(signature, 0, sizeof(signature));
	sig_len = len - 8;
	in_uint8a(s, signature, sig_len);
    if(rdssl_sign_ok((char *)exponent, SEC_EXPONENT_SIZE, (char *)modulus, g_server_public_key_len,
                     (char *)signature_, SEC_MODULUS_SIZE, (char *)signature, sig_len, (char *)g_testkey))
    {
        DEBUG_RDP5(("key signature doesn't match test key\n"));
    }
	return s_check(s);
}