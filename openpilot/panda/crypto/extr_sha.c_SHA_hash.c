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
typedef  int /*<<< orphan*/  const uint8_t ;
typedef  int /*<<< orphan*/  SHA_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  SHA_DIGEST_SIZE ; 
 int /*<<< orphan*/  SHA_final (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA_update (int /*<<< orphan*/ *,void const*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

const uint8_t* SHA_hash(const void* data, int len, uint8_t* digest) {
    SHA_CTX ctx;
    SHA_init(&ctx);
    SHA_update(&ctx, data, len);
    memcpy(digest, SHA_final(&ctx), SHA_DIGEST_SIZE);
    return digest;
}