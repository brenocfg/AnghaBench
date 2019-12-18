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
typedef  int /*<<< orphan*/  uint8 ;

/* Variables and functions */
 int /*<<< orphan*/  rdssl_sha1_clear (void*) ; 
 int /*<<< orphan*/  rdssl_sha1_complete (void**,char*) ; 
 void* rdssl_sha1_info_create () ; 
 int /*<<< orphan*/  rdssl_sha1_info_delete (void*) ; 
 int /*<<< orphan*/  rdssl_sha1_transform (void**,char*,int) ; 

void
sec_hash_sha1_16(uint8 * out, uint8 * in, uint8 * salt1)
{
	void * sha;
	sha = rdssl_sha1_info_create();
	rdssl_sha1_clear(sha);
	rdssl_sha1_transform(&sha, (char *)in, 16);
	rdssl_sha1_transform(&sha, (char *)salt1, 16);
	rdssl_sha1_complete(&sha, (char *)out);
	rdssl_sha1_info_delete(sha);
}