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
typedef  int /*<<< orphan*/  ULong ;
struct TYPE_4__ {int k; int maxwds; scalar_t__ wds; scalar_t__ sign; struct TYPE_4__* next; } ;
typedef  TYPE_1__ Bigint ;

/* Variables and functions */
 int /*<<< orphan*/  ACQUIRE_DTOA_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_ERROR ; 
 int /*<<< orphan*/  FREE_DTOA_LOCK (int /*<<< orphan*/ ) ; 
 int Kmax ; 
 scalar_t__ MALLOC (unsigned int) ; 
 scalar_t__ PRIVATE_mem ; 
 TYPE_1__** freelist ; 
 scalar_t__ pmem_next ; 
 scalar_t__ private_mem ; 
 int /*<<< orphan*/  zend_error_noreturn (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static Bigint *
Balloc
#ifdef KR_headers
	(k) int k;
#else
	(int k)
#endif
{
	int x;
	Bigint *rv;
#ifndef Omit_Private_Memory
	unsigned int len;
#endif

	ACQUIRE_DTOA_LOCK(0);
	/* The k > Kmax case does not need ACQUIRE_DTOA_LOCK(0), */
	/* but this case seems very unlikely. */
	if (k <= Kmax && (rv = freelist[k]))
		freelist[k] = rv->next;
	else {
		x = 1 << k;
#ifdef Omit_Private_Memory
		rv = (Bigint *)MALLOC(sizeof(Bigint) + (x-1)*sizeof(ULong));
		if (!rv) {
			FREE_DTOA_LOCK(0);
			zend_error_noreturn(E_ERROR, "Balloc() failed to allocate memory");
		}
#else
		len = (sizeof(Bigint) + (x-1)*sizeof(ULong) + sizeof(double) - 1)
			/sizeof(double);
		if (k <= Kmax && pmem_next - private_mem + len <= PRIVATE_mem) {
			rv = (Bigint*)pmem_next;
			pmem_next += len;
			}
		else
			rv = (Bigint*)MALLOC(len*sizeof(double));
			if (!rv) {
				FREE_DTOA_LOCK(0);
				zend_error_noreturn(E_ERROR, "Balloc() failed to allocate memory");
			}
#endif
		rv->k = k;
		rv->maxwds = x;
		}
	FREE_DTOA_LOCK(0);
	rv->sign = rv->wds = 0;
	return rv;
	}