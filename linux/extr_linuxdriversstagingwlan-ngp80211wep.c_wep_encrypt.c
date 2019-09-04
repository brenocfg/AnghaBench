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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct wlandevice {scalar_t__* wep_keylens; int /*<<< orphan*/ * wep_keys; } ;

/* Variables and functions */
 int NUM_WEPKEYS ; 
 int /*<<< orphan*/  get_random_bytes (int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  swap (scalar_t__,scalar_t__) ; 
 scalar_t__* wep_crc32_table ; 

int wep_encrypt(struct wlandevice *wlandev, u8 *buf,
		u8 *dst, u32 len, int keynum, u8 *iv, u8 *icv)
{
	u32 i, j, k, crc, keylen;
	u8 s[256], key[64];

	/* no point in WEPping an empty frame */
	if (len <= 0)
		return -1;

	/* we need to have a real key.. */
	if (keynum >= NUM_WEPKEYS)
		return -2;
	keylen = wlandev->wep_keylens[keynum];
	if (keylen <= 0)
		return -3;

	/* use a random IV.  And skip known weak ones. */
	get_random_bytes(iv, 3);
	while ((iv[1] == 0xff) && (iv[0] >= 3) && (iv[0] < keylen))
		get_random_bytes(iv, 3);

	iv[3] = (keynum & 0x03) << 6;

	key[0] = iv[0];
	key[1] = iv[1];
	key[2] = iv[2];

	/* copy the rest of the key over from the designated key */
	memcpy(key + 3, wlandev->wep_keys[keynum], keylen);

	keylen += 3;		/* add in IV bytes */

	/* set up the RC4 state */
	for (i = 0; i < 256; i++)
		s[i] = i;
	j = 0;
	for (i = 0; i < 256; i++) {
		j = (j + s[i] + key[i % keylen]) & 0xff;
		swap(i, j);
	}

	/* Update CRC32 then apply RC4 to the data */
	crc = ~0;
	i = 0;
	j = 0;
	for (k = 0; k < len; k++) {
		crc = wep_crc32_table[(crc ^ buf[k]) & 0xff] ^ (crc >> 8);
		i = (i + 1) & 0xff;
		j = (j + s[i]) & 0xff;
		swap(i, j);
		dst[k] = buf[k] ^ s[(s[i] + s[j]) & 0xff];
	}
	crc = ~crc;

	/* now let's encrypt the crc */
	icv[0] = crc;
	icv[1] = crc >> 8;
	icv[2] = crc >> 16;
	icv[3] = crc >> 24;

	for (k = 0; k < 4; k++) {
		i = (i + 1) & 0xff;
		j = (j + s[i]) & 0xff;
		swap(i, j);
		icv[k] ^= s[(s[i] + s[j]) & 0xff];
	}

	return 0;
}