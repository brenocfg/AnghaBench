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
 int /*<<< orphan*/  rdssl_hash_transform (void*,char*,int) ; 

void
rdssl_sha1_transform(void* sha1_info, char* data, int len)
{
    rdssl_hash_transform(sha1_info, data, len);
}