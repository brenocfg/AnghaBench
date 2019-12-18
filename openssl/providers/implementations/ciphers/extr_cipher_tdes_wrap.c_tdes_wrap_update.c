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
 int /*<<< orphan*/  PROV_R_CIPHER_OPERATION_FAILED ; 
 int /*<<< orphan*/  PROV_R_OUTPUT_BUFFER_TOO_SMALL ; 
 int /*<<< orphan*/  PROVerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tdes_wrap_cipher (void*,unsigned char*,size_t*,size_t,unsigned char const*,size_t) ; 

__attribute__((used)) static int tdes_wrap_update(void *vctx, unsigned char *out, size_t *outl,
                            size_t outsize, const unsigned char *in,
                            size_t inl)
{
    *outl = 0;
    if (outsize < inl) {
        PROVerr(0, PROV_R_OUTPUT_BUFFER_TOO_SMALL);
        return 0;
    }

    if (!tdes_wrap_cipher(vctx, out, outl, outsize, in, inl)) {
        PROVerr(0, PROV_R_CIPHER_OPERATION_FAILED);
        return 0;
    }
    return 1;
}