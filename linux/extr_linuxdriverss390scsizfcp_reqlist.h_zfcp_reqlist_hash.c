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
 unsigned long ZFCP_REQ_LIST_BUCKETS ; 

__attribute__((used)) static inline int zfcp_reqlist_hash(unsigned long req_id)
{
	return req_id % ZFCP_REQ_LIST_BUCKETS;
}