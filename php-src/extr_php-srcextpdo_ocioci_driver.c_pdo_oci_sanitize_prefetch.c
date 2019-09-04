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
typedef  int /*<<< orphan*/  ub4 ;

/* Variables and functions */
 long PDO_OCI_PREFETCH_DEFAULT ; 
 long PDO_OCI_PREFETCH_ROWSIZE ; 
 long UB4MAXVAL ; 

__attribute__((used)) static inline ub4 pdo_oci_sanitize_prefetch(long prefetch) /* {{{ */
{
	if (prefetch < 0) {
		prefetch = 0;
	} else if (prefetch > UB4MAXVAL / PDO_OCI_PREFETCH_ROWSIZE) {
		prefetch = PDO_OCI_PREFETCH_DEFAULT;
	}
	return ((ub4)prefetch);
}