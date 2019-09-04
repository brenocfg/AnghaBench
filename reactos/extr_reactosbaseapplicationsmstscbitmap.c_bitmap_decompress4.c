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
typedef  int /*<<< orphan*/  uint8 ;
typedef  int RD_BOOL ;

/* Variables and functions */
 int CVAL (int /*<<< orphan*/ *) ; 
 int False ; 
 int process_plane (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static RD_BOOL
bitmap_decompress4(uint8 * output, int width, int height, uint8 * input, int size)
{
	int code;
	int bytes_pro;
	int total_pro;

	code = CVAL(input);
	if (code != 0x10)
	{
		return False;
	}
	total_pro = 1;
	bytes_pro = process_plane(input, width, height, output + 3, size - total_pro);
	total_pro += bytes_pro;
	input += bytes_pro;
	bytes_pro = process_plane(input, width, height, output + 2, size - total_pro);
	total_pro += bytes_pro;
	input += bytes_pro;
	bytes_pro = process_plane(input, width, height, output + 1, size - total_pro);
	total_pro += bytes_pro;
	input += bytes_pro;
	bytes_pro = process_plane(input, width, height, output + 0, size - total_pro);
	total_pro += bytes_pro;
	return size == total_pro;
}