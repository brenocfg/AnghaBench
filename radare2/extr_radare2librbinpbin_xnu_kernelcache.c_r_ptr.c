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
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
typedef  int /*<<< orphan*/  RKernelCacheObj ;

/* Variables and functions */
 int /*<<< orphan*/  K_PPTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_read_le64 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ut64 r_ptr (ut8 *buf, RKernelCacheObj *obj) {
	ut64 decorated_addr = r_read_le64 (buf);
	return K_PPTR (decorated_addr);
}