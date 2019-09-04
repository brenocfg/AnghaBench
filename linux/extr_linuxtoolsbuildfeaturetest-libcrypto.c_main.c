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
typedef  int /*<<< orphan*/  dat ;
typedef  int /*<<< orphan*/  MD5_CTX ;

/* Variables and functions */
 int MD5_DIGEST_LENGTH ; 
 int /*<<< orphan*/  MD5_Final (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5_Update (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  SHA1 (unsigned char*,int,unsigned char*) ; 
 int SHA_DIGEST_LENGTH ; 

int main(void)
{
	MD5_CTX context;
	unsigned char md[MD5_DIGEST_LENGTH + SHA_DIGEST_LENGTH];
	unsigned char dat[] = "12345";

	MD5_Init(&context);
	MD5_Update(&context, &dat[0], sizeof(dat));
	MD5_Final(&md[0], &context);

	SHA1(&dat[0], sizeof(dat), &md[0]);

	return 0;
}