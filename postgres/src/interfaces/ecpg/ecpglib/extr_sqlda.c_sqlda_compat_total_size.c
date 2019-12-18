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
typedef  enum COMPAT_MODE { ____Placeholder_COMPAT_MODE } COMPAT_MODE ;
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 long sqlda_common_total_size (int /*<<< orphan*/  const*,int,int,long) ; 
 long sqlda_compat_empty_size (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static long
sqlda_compat_total_size(const PGresult *res, int row, enum COMPAT_MODE compat)
{
	long		offset;

	offset = sqlda_compat_empty_size(res);

	if (row < 0)
		return offset;

	offset = sqlda_common_total_size(res, row, compat, offset);
	return offset;
}