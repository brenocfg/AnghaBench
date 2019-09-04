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
typedef  int /*<<< orphan*/  matrix ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (float*,float**,int) ; 

__attribute__((used)) static void
nk_d3d9_get_projection_matrix(int width, int height, float *result)
{
    const float L = 0.5f;
    const float R = (float)width + 0.5f;
    const float T = 0.5f;
    const float B = (float)height + 0.5f;
    float matrix[4][4] = {
        {    2.0f / (R - L),              0.0f, 0.0f, 0.0f },
        {              0.0f,    2.0f / (T - B), 0.0f, 0.0f },
        {              0.0f,              0.0f, 0.0f, 0.0f },
        { (R + L) / (L - R), (T + B) / (B - T), 0.0f, 1.0f },
    };
    memcpy(result, matrix, sizeof(matrix));
}