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
struct ecryptfs_crypt_stat {int /*<<< orphan*/  metadata_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECRYPTFS_MINIMUM_HEADER_EXTENT_SIZE ; 

__attribute__((used)) static void set_default_header_data(struct ecryptfs_crypt_stat *crypt_stat)
{
	crypt_stat->metadata_size = ECRYPTFS_MINIMUM_HEADER_EXTENT_SIZE;
}