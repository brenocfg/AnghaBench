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
 int /*<<< orphan*/  rdssl_md5_clear (void*) ; 
 int /*<<< orphan*/  rdssl_md5_complete (void*,char*) ; 
 void* rdssl_md5_info_create () ; 
 int /*<<< orphan*/  rdssl_md5_info_delete (void*) ; 
 int /*<<< orphan*/  rdssl_md5_transform (void*,char*,int) ; 

void
sec_hash_16(uint8 * out, uint8 * in, uint8 * salt1, uint8 * salt2)
{
	void * md5;
	
	md5 = rdssl_md5_info_create();
	rdssl_md5_clear(md5);
	rdssl_md5_transform(md5, (char *)in, 16);
	rdssl_md5_transform(md5, (char *)salt1, 32);
	rdssl_md5_transform(md5, (char *)salt2, 32);
    rdssl_md5_complete(md5, (char *)out);
	rdssl_md5_info_delete(md5);
}