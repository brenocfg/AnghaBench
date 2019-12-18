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
struct sqlvar_struct {int dummy; } ;
struct sqlda_struct {int dummy; } ;
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 int PQnfields (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ecpg_sqlda_align_add_size (long,int,int /*<<< orphan*/ ,long*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static long
sqlda_native_empty_size(const PGresult *res)
{
	long		offset;
	int			sqld = PQnfields(res);

	/* Initial size to store main structure and field structures */
	offset = sizeof(struct sqlda_struct) + (sqld - 1) * sizeof(struct sqlvar_struct);

	/* Add padding to the first field value */
	ecpg_sqlda_align_add_size(offset, sizeof(int), 0, &offset, NULL);

	return offset;
}