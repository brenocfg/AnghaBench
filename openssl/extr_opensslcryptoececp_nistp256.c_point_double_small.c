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
typedef  int /*<<< orphan*/  smallfelem ;
typedef  int /*<<< orphan*/  felem ;

/* Variables and functions */
 int /*<<< orphan*/  felem_shrink (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  point_double (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smallfelem_expand (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void
point_double_small(smallfelem x_out, smallfelem y_out, smallfelem z_out,
                   const smallfelem x_in, const smallfelem y_in,
                   const smallfelem z_in)
{
    felem felem_x_out, felem_y_out, felem_z_out;
    felem felem_x_in, felem_y_in, felem_z_in;

    smallfelem_expand(felem_x_in, x_in);
    smallfelem_expand(felem_y_in, y_in);
    smallfelem_expand(felem_z_in, z_in);
    point_double(felem_x_out, felem_y_out, felem_z_out,
                 felem_x_in, felem_y_in, felem_z_in);
    felem_shrink(x_out, felem_x_out);
    felem_shrink(y_out, felem_y_out);
    felem_shrink(z_out, felem_z_out);
}