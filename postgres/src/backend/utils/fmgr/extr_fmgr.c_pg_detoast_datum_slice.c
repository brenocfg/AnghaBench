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
struct varlena {int dummy; } ;
typedef  int /*<<< orphan*/  int32 ;

/* Variables and functions */
 struct varlena* detoast_attr_slice (struct varlena*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct varlena *
pg_detoast_datum_slice(struct varlena *datum, int32 first, int32 count)
{
	/* Only get the specified portion from the toast rel */
	return detoast_attr_slice(datum, first, count);
}