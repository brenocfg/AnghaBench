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
 int g_rc4_key_len ; 
 scalar_t__ pad_54 ; 
 scalar_t__ pad_92 ; 
 int /*<<< orphan*/  rdssl_md5_clear (void*) ; 
 int /*<<< orphan*/  rdssl_md5_complete (void*,char*) ; 
 void* rdssl_md5_info_create () ; 
 int /*<<< orphan*/  rdssl_md5_info_delete (void*) ; 
 int /*<<< orphan*/  rdssl_md5_transform (void*,char*,int) ; 
 int /*<<< orphan*/  rdssl_rc4_crypt (void*,char*,char*,int) ; 
 void* rdssl_rc4_info_create () ; 
 int /*<<< orphan*/  rdssl_rc4_info_delete (void*) ; 
 int /*<<< orphan*/  rdssl_rc4_set_key (void*,char*,int) ; 
 int /*<<< orphan*/  rdssl_sha1_clear (void*) ; 
 int /*<<< orphan*/  rdssl_sha1_complete (void*,char*) ; 
 void* rdssl_sha1_info_create () ; 
 int /*<<< orphan*/  rdssl_sha1_info_delete (void*) ; 
 int /*<<< orphan*/  rdssl_sha1_transform (void*,char*,int) ; 
 int /*<<< orphan*/  sec_make_40bit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
sec_update(uint8 * key, uint8 * update_key)
{
	uint8 shasig[20];
	void * sha;
	void * md5;
	void * update;

	sha = rdssl_sha1_info_create();
	rdssl_sha1_clear(sha);
	rdssl_sha1_transform(sha, (char *)update_key, g_rc4_key_len);
	rdssl_sha1_transform(sha, (char *)pad_54, 40);
	rdssl_sha1_transform(sha, (char *)key, g_rc4_key_len);
	rdssl_sha1_complete(sha, (char *)shasig);
	rdssl_sha1_info_delete(sha);

	md5 = rdssl_md5_info_create();
	rdssl_md5_clear(md5);
    rdssl_md5_transform(md5, (char *)update_key, g_rc4_key_len);
	rdssl_md5_transform(md5, (char *)pad_92, 48);
	rdssl_md5_transform(md5, (char *)shasig, 20);
	rdssl_md5_complete(md5, (char *)key);
	rdssl_md5_info_delete(md5);


	update = rdssl_rc4_info_create();
	rdssl_rc4_set_key(update, (char *)key, g_rc4_key_len);
	rdssl_rc4_crypt(update, (char *)key, (char *)key, g_rc4_key_len);
	rdssl_rc4_info_delete(update);

	if (g_rc4_key_len == 8)
		sec_make_40bit(key);
}