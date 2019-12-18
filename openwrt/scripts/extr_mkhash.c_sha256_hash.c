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
typedef  int /*<<< orphan*/  SHA256_CTX ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int SHA256_DIGEST_LENGTH ; 
 int /*<<< orphan*/  SHA256_Final (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA256_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA256_Update (int /*<<< orphan*/ *,void*,int) ; 
 void* hash_buf (int /*<<< orphan*/ *,int*) ; 
 char const* hash_string (unsigned char*,int) ; 

__attribute__((used)) static const char *sha256_hash(FILE *f)
{
	SHA256_CTX ctx;
	unsigned char val[SHA256_DIGEST_LENGTH];
	void *buf;
	int len;

	SHA256_Init(&ctx);
	while ((buf = hash_buf(f, &len)) != NULL)
		SHA256_Update(&ctx, buf, len);
	SHA256_Final(val, &ctx);

	return hash_string(val, SHA256_DIGEST_LENGTH);
}