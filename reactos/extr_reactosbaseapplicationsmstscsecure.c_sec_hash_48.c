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
typedef  scalar_t__ uint8 ;

/* Variables and functions */
 int /*<<< orphan*/  memset (scalar_t__*,scalar_t__,int) ; 
 int /*<<< orphan*/  rdssl_md5_clear (void*) ; 
 int /*<<< orphan*/  rdssl_md5_complete (void*,char*) ; 
 void* rdssl_md5_info_create () ; 
 int /*<<< orphan*/  rdssl_md5_info_delete (void*) ; 
 int /*<<< orphan*/  rdssl_md5_transform (void*,char*,int) ; 
 int /*<<< orphan*/  rdssl_sha1_clear (void*) ; 
 int /*<<< orphan*/  rdssl_sha1_complete (void*,char*) ; 
 void* rdssl_sha1_info_create () ; 
 int /*<<< orphan*/  rdssl_sha1_info_delete (void*) ; 
 int /*<<< orphan*/  rdssl_sha1_transform (void*,char*,int) ; 

void
sec_hash_48(uint8 * out, uint8 * in, uint8 * salt1, uint8 * salt2, uint8 salt)
{
	uint8 shasig[20];
	uint8 pad[4];
	void * sha;
	void * md5;
	int i;

	for (i = 0; i < 3; i++)
	{
		memset(pad, salt + i, i + 1);
		sha = rdssl_sha1_info_create();
		rdssl_sha1_clear(sha);
		rdssl_sha1_transform(sha, (char *)pad, i + 1);
		rdssl_sha1_transform(sha, (char *)in, 48);
		rdssl_sha1_transform(sha, (char *)salt1, 32);
		rdssl_sha1_transform(sha, (char *)salt2, 32);
		rdssl_sha1_complete(sha, (char *)shasig);
		rdssl_sha1_info_delete(sha);
		md5 = rdssl_md5_info_create();
		rdssl_md5_clear(md5);
        rdssl_md5_transform(md5, (char *)in, 48);
        rdssl_md5_transform(md5, (char *)shasig, 20);
		rdssl_md5_complete(md5, (char *)out + i * 16);
		rdssl_md5_info_delete(md5);
	}
}