#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int int32 ;
struct TYPE_3__ {int maxvalues; scalar_t__ nvalues; int /*<<< orphan*/ * categories; int /*<<< orphan*/ * keys; } ;
typedef  TYPE_1__ KeyArray ;
typedef  int /*<<< orphan*/  GinNullCategory ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 scalar_t__ palloc (int) ; 

__attribute__((used)) static void
initKeyArray(KeyArray *keys, int32 maxvalues)
{
	keys->keys = (Datum *) palloc(sizeof(Datum) * maxvalues);
	keys->categories = (GinNullCategory *)
		palloc(sizeof(GinNullCategory) * maxvalues);
	keys->nvalues = 0;
	keys->maxvalues = maxvalues;
}