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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  bf_key ;

/* Variables and functions */
 int /*<<< orphan*/  KEYBYTES ; 
 int /*<<< orphan*/  bf_enc (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bf_setkey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rtmpe9_keys ; 

__attribute__((used)) static void rtmpe9_sig(uint8_t *in, uint8_t *out, int keyid)
{
    uint32_t d[2];
    bf_key key;

    bf_setkey(rtmpe9_keys[keyid], KEYBYTES, &key);

    /* input is little-endian */
    d[0] = in[0] | (in[1] << 8) | (in[2] << 16) | (in[3] << 24);
    d[1] = in[4] | (in[5] << 8) | (in[6] << 16) | (in[7] << 24);
    bf_enc(d, &key);
    out[0] = d[0] & 0xff;
    out[1] = (d[0] >> 8) & 0xff;
    out[2] = (d[0] >> 16) & 0xff;
    out[3] = (d[0] >> 24) & 0xff;
    out[4] = d[1] & 0xff;
    out[5] = (d[1] >> 8) & 0xff;
    out[6] = (d[1] >> 16) & 0xff;
    out[7] = (d[1] >> 24) & 0xff;
}