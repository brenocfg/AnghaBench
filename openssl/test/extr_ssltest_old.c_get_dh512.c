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
typedef  int /*<<< orphan*/  dh512_p ;
typedef  int /*<<< orphan*/  dh512_g ;
typedef  int /*<<< orphan*/  DH ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/ * BN_bin2bn (unsigned char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DH_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * DH_new () ; 
 int /*<<< orphan*/  DH_set0_pqg (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static DH *get_dh512(void)
{
    static unsigned char dh512_p[] = {
        0xCB, 0xC8, 0xE1, 0x86, 0xD0, 0x1F, 0x94, 0x17, 0xA6, 0x99, 0xF0,
        0xC6,
        0x1F, 0x0D, 0xAC, 0xB6, 0x25, 0x3E, 0x06, 0x39, 0xCA, 0x72, 0x04,
        0xB0,
        0x6E, 0xDA, 0xC0, 0x61, 0xE6, 0x7A, 0x77, 0x25, 0xE8, 0x3B, 0xB9,
        0x5F,
        0x9A, 0xB6, 0xB5, 0xFE, 0x99, 0x0B, 0xA1, 0x93, 0x4E, 0x35, 0x33,
        0xB8,
        0xE1, 0xF1, 0x13, 0x4F, 0x59, 0x1A, 0xD2, 0x57, 0xC0, 0x26, 0x21,
        0x33,
        0x02, 0xC5, 0xAE, 0x23,
    };
    static unsigned char dh512_g[] = {
        0x02,
    };
    DH *dh;
    BIGNUM *p, *g;

    if ((dh = DH_new()) == NULL)
        return NULL;
    p = BN_bin2bn(dh512_p, sizeof(dh512_p), NULL);
    g = BN_bin2bn(dh512_g, sizeof(dh512_g), NULL);
    if ((p == NULL) || (g == NULL) || !DH_set0_pqg(dh, p, NULL, g)) {
        DH_free(dh);
        BN_free(p);
        BN_free(g);
        return NULL;
    }
    return dh;
}