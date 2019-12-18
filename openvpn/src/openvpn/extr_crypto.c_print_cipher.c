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
typedef  int /*<<< orphan*/  cipher_kt_t ;

/* Variables and functions */
 int cipher_kt_block_size (int /*<<< orphan*/  const*) ; 
 int cipher_kt_key_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  cipher_kt_mode_cbc (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  cipher_kt_name (int /*<<< orphan*/  const*) ; 
 scalar_t__ cipher_kt_var_key_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* translate_cipher_name_to_openvpn (int /*<<< orphan*/ ) ; 

void
print_cipher(const cipher_kt_t *cipher)
{
    const char *var_key_size = cipher_kt_var_key_size(cipher) ?
                               " by default" : "";

    printf("%s  (%d bit key%s, ",
           translate_cipher_name_to_openvpn(cipher_kt_name(cipher)),
           cipher_kt_key_size(cipher) * 8, var_key_size);

    if (cipher_kt_block_size(cipher) == 1)
    {
        printf("stream cipher");
    }
    else
    {
        printf("%d bit block", cipher_kt_block_size(cipher) * 8);
    }

    if (!cipher_kt_mode_cbc(cipher))
    {
        printf(", TLS client/server mode only");
    }

    printf(")\n");
}