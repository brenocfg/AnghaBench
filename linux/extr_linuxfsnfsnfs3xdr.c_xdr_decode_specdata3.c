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
typedef  int /*<<< orphan*/  dev_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 unsigned int MAJOR (int /*<<< orphan*/ ) ; 
 unsigned int MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKDEV (unsigned int,unsigned int) ; 
 unsigned int be32_to_cpup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __be32 *xdr_decode_specdata3(__be32 *p, dev_t *rdev)
{
	unsigned int major, minor;

	major = be32_to_cpup(p++);
	minor = be32_to_cpup(p++);
	*rdev = MKDEV(major, minor);
	if (MAJOR(*rdev) != major || MINOR(*rdev) != minor)
		*rdev = 0;
	return p;
}