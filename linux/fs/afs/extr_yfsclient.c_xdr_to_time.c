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
struct yfs_xdr_u64 {int dummy; } ;
struct timespec64 {int dummy; } ;
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */
 int /*<<< orphan*/  xdr_to_u64 (struct yfs_xdr_u64 const) ; 
 struct timespec64 yfs_time_to_linux (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct timespec64 xdr_to_time(const struct yfs_xdr_u64 xdr)
{
	s64 t = xdr_to_u64(xdr);

	return yfs_time_to_linux(t);
}