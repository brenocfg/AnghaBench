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
struct aa_loaddata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int /*<<< orphan*/ ) ; 
 struct aa_loaddata* __aa_get_loaddata (struct aa_loaddata*) ; 

__attribute__((used)) static inline struct aa_loaddata *
aa_get_loaddata(struct aa_loaddata *data)
{
	struct aa_loaddata *tmp = __aa_get_loaddata(data);

	AA_BUG(data && !tmp);

	return tmp;
}