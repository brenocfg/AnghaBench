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
typedef  int /*<<< orphan*/  tmp_key ;
typedef  int /*<<< orphan*/  cs_sha1_ctx ;
typedef  int /*<<< orphan*/  buf2 ;
typedef  int /*<<< orphan*/  buf1 ;

/* Variables and functions */
 int /*<<< orphan*/  cs_sha1_final (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cs_sha1_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cs_sha1_update (int /*<<< orphan*/ *,unsigned char const*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 

void cs_hmac_sha1(const unsigned char *key, size_t keylen,
                  const unsigned char *data, size_t datalen,
                  unsigned char out[20]) {
  cs_sha1_ctx ctx;
  unsigned char buf1[64], buf2[64], tmp_key[20], i;

  if (keylen > sizeof(buf1)) {
    cs_sha1_init(&ctx);
    cs_sha1_update(&ctx, key, keylen);
    cs_sha1_final(tmp_key, &ctx);
    key = tmp_key;
    keylen = sizeof(tmp_key);
  }

  memset(buf1, 0, sizeof(buf1));
  memset(buf2, 0, sizeof(buf2));
  memcpy(buf1, key, keylen);
  memcpy(buf2, key, keylen);

  for (i = 0; i < sizeof(buf1); i++) {
    buf1[i] ^= 0x36;
    buf2[i] ^= 0x5c;
  }

  cs_sha1_init(&ctx);
  cs_sha1_update(&ctx, buf1, sizeof(buf1));
  cs_sha1_update(&ctx, data, datalen);
  cs_sha1_final(out, &ctx);

  cs_sha1_init(&ctx);
  cs_sha1_update(&ctx, buf2, sizeof(buf2));
  cs_sha1_update(&ctx, out, 20);
  cs_sha1_final(out, &ctx);
}