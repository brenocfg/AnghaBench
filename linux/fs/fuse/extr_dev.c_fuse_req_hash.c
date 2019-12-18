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
typedef  int u64 ;

/* Variables and functions */
 int FUSE_INT_REQ_BIT ; 
 int /*<<< orphan*/  FUSE_PQ_HASH_BITS ; 
 unsigned int hash_long (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int fuse_req_hash(u64 unique)
{
	return hash_long(unique & ~FUSE_INT_REQ_BIT, FUSE_PQ_HASH_BITS);
}