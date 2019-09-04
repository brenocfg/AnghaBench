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
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  PROV_F_UNPADBLOCK ; 
 int /*<<< orphan*/  PROV_R_BAD_DECRYPT ; 
 int /*<<< orphan*/  PROVerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int unpadblock(unsigned char *buf, size_t *buflen, size_t blocksize)
{
    size_t pad, i;
    size_t len = *buflen;

    if(len != blocksize) {
        PROVerr(PROV_F_UNPADBLOCK, ERR_R_INTERNAL_ERROR);
        return 0;
    }

    /*
     * The following assumes that the ciphertext has been authenticated.
     * Otherwise it provides a padding oracle.
     */
    pad = buf[blocksize - 1];
    if (pad == 0 || pad > blocksize) {
        PROVerr(PROV_F_UNPADBLOCK, PROV_R_BAD_DECRYPT);
        return 0;
    }
    for (i = 0; i < pad; i++) {
        if (buf[--len] != pad) {
            PROVerr(PROV_F_UNPADBLOCK, PROV_R_BAD_DECRYPT);
            return 0;
        }
    }
    *buflen = len;
    return 1;
}