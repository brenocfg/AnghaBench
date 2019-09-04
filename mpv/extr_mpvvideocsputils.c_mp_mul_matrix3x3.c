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

__attribute__((used)) static void mp_mul_matrix3x3(float a[3][3], float b[3][3])
{
    float a00 = a[0][0], a01 = a[0][1], a02 = a[0][2],
          a10 = a[1][0], a11 = a[1][1], a12 = a[1][2],
          a20 = a[2][0], a21 = a[2][1], a22 = a[2][2];

    for (int i = 0; i < 3; i++) {
        a[0][i] = a00 * b[0][i] + a01 * b[1][i] + a02 * b[2][i];
        a[1][i] = a10 * b[0][i] + a11 * b[1][i] + a12 * b[2][i];
        a[2][i] = a20 * b[0][i] + a21 * b[1][i] + a22 * b[2][i];
    }
}