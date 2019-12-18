#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ private_data; } ;
typedef  TYPE_1__ pagetable_hash ;
struct TYPE_5__ {int /*<<< orphan*/  dsapagetableold; int /*<<< orphan*/ * dsa; } ;
typedef  TYPE_2__ TIDBitmap ;

/* Variables and functions */
 scalar_t__ DsaPointerIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidDsaPointer ; 
 int /*<<< orphan*/  dsa_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (void*) ; 

__attribute__((used)) static inline void
pagetable_free(pagetable_hash *pagetable, void *pointer)
{
	TIDBitmap  *tbm = (TIDBitmap *) pagetable->private_data;

	/* pfree the input pointer if DSA is not available */
	if (tbm->dsa == NULL)
		pfree(pointer);
	else if (DsaPointerIsValid(tbm->dsapagetableold))
	{
		dsa_free(tbm->dsa, tbm->dsapagetableold);
		tbm->dsapagetableold = InvalidDsaPointer;
	}
}