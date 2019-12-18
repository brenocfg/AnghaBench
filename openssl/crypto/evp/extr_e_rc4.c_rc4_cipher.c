#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  ks; } ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  RC4 (int /*<<< orphan*/ *,size_t,unsigned char const*,unsigned char*) ; 
 TYPE_1__* data (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rc4_cipher(EVP_CIPHER_CTX *ctx, unsigned char *out,
                      const unsigned char *in, size_t inl)
{
    RC4(&data(ctx)->ks, inl, in, out);
    return 1;
}