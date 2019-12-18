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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  md_kt_t ;
typedef  int /*<<< orphan*/  hmac_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  hmac_ctx_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hmac_ctx_final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hmac_ctx_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hmac_ctx_init (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * hmac_ctx_new () ; 
 int /*<<< orphan*/  hmac_ctx_update (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/ * md_kt_get (char*) ; 

__attribute__((used)) static void
gen_hmac_md5(const uint8_t *data, int data_len, const uint8_t *key, int key_len,
             uint8_t *result)
{
    const md_kt_t *md5_kt = md_kt_get("MD5");
    hmac_ctx_t *hmac_ctx = hmac_ctx_new();

    hmac_ctx_init(hmac_ctx, key, key_len, md5_kt);
    hmac_ctx_update(hmac_ctx, data, data_len);
    hmac_ctx_final(hmac_ctx, result);
    hmac_ctx_cleanup(hmac_ctx);
    hmac_ctx_free(hmac_ctx);
}