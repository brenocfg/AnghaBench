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
struct gf_poly {int /*<<< orphan*/  deg; } ;

/* Variables and functions */
 int /*<<< orphan*/  GF_POLY_SZ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct gf_poly*,struct gf_poly*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gf_poly_copy(struct gf_poly *dst, struct gf_poly *src)
{
	memcpy(dst, src, GF_POLY_SZ(src->deg));
}