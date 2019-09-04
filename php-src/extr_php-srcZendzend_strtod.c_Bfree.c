#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t k; struct TYPE_4__* next; } ;
typedef  TYPE_1__ Bigint ;

/* Variables and functions */
 int /*<<< orphan*/  ACQUIRE_DTOA_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FREE_DTOA_LOCK (int /*<<< orphan*/ ) ; 
 size_t Kmax ; 
 int /*<<< orphan*/  free (void*) ; 
 TYPE_1__** freelist ; 

__attribute__((used)) static void
Bfree
#ifdef KR_headers
	(v) Bigint *v;
#else
	(Bigint *v)
#endif
{
	if (v) {
		if (v->k > Kmax)
#ifdef FREE
			FREE((void*)v);
#else
			free((void*)v);
#endif
		else {
			ACQUIRE_DTOA_LOCK(0);
			v->next = freelist[v->k];
			freelist[v->k] = v;
			FREE_DTOA_LOCK(0);
			}
		}
	}