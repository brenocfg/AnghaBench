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

/* Variables and functions */
 int /*<<< orphan*/  CALG_MD5 ; 
 void* rdssl_hash_info_create (int /*<<< orphan*/ ) ; 

void*
rdssl_md5_info_create(void)
{
    return rdssl_hash_info_create(CALG_MD5);
}