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
typedef  int /*<<< orphan*/  u8 ;
struct nd_pfn {int /*<<< orphan*/ * uuid; } ;
struct nd_namespace_pmem {int /*<<< orphan*/ * uuid; } ;
struct nd_namespace_blk {int /*<<< orphan*/ * uuid; } ;
struct nd_btt {int /*<<< orphan*/ * uuid; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  NSLABEL_UUID_LEN ; 
 scalar_t__ is_namespace_blk (struct device*) ; 
 scalar_t__ is_namespace_pmem (struct device*) ; 
 scalar_t__ is_nd_btt (struct device*) ; 
 scalar_t__ is_nd_pfn (struct device*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct nd_btt* to_nd_btt (struct device*) ; 
 struct nd_namespace_blk* to_nd_namespace_blk (struct device*) ; 
 struct nd_namespace_pmem* to_nd_namespace_pmem (struct device*) ; 
 struct nd_pfn* to_nd_pfn (struct device*) ; 

__attribute__((used)) static int is_uuid_busy(struct device *dev, void *data)
{
	u8 *uuid1 = data, *uuid2 = NULL;

	if (is_namespace_pmem(dev)) {
		struct nd_namespace_pmem *nspm = to_nd_namespace_pmem(dev);

		uuid2 = nspm->uuid;
	} else if (is_namespace_blk(dev)) {
		struct nd_namespace_blk *nsblk = to_nd_namespace_blk(dev);

		uuid2 = nsblk->uuid;
	} else if (is_nd_btt(dev)) {
		struct nd_btt *nd_btt = to_nd_btt(dev);

		uuid2 = nd_btt->uuid;
	} else if (is_nd_pfn(dev)) {
		struct nd_pfn *nd_pfn = to_nd_pfn(dev);

		uuid2 = nd_pfn->uuid;
	}

	if (uuid2 && memcmp(uuid1, uuid2, NSLABEL_UUID_LEN) == 0)
		return -EBUSY;

	return 0;
}