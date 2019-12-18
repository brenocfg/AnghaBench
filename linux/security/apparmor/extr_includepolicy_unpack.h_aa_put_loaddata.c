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
struct aa_loaddata {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  aa_loaddata_kref ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void aa_put_loaddata(struct aa_loaddata *data)
{
	if (data)
		kref_put(&data->count, aa_loaddata_kref);
}