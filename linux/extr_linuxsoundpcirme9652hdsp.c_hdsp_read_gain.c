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
struct hdsp {int* mixer_matrix; } ;

/* Variables and functions */
 unsigned int HDSP_MATRIX_MIXER_SIZE ; 

__attribute__((used)) static int hdsp_read_gain (struct hdsp *hdsp, unsigned int addr)
{
	if (addr >= HDSP_MATRIX_MIXER_SIZE)
		return 0;

	return hdsp->mixer_matrix[addr];
}