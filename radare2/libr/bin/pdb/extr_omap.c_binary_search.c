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

/* Variables and functions */

__attribute__((used)) static int binary_search(unsigned int *A, int key, int imin, int imax) {
	int imid;

	// continually narrow search until just one element remains
	while (imin < imax) {
		imid = (imin + imax) / 2;
		if (A[imid] < key) {
			imin = imid + 1;
		} else {
			imax = imid;
		}
	}
	// At exit of while:
	//   if A[] is empty, then imax < imin
	//   otherwise imax == imin

	// deferred test for equality
	if ((imax == imin) && (A[imin] == key)) {
		return imin;
	}
	return -1;
}