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
typedef  union VALUETYPE {int dummy; } VALUETYPE ;
struct r_magic {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DO_CVT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h ; 
 int /*<<< orphan*/  ut16 ; 

__attribute__((used)) static void cvt_16(union VALUETYPE *p, const struct r_magic *m) {
	DO_CVT (h, (ut16));
}