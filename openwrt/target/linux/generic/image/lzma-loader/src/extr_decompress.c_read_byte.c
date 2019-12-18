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
typedef  int UInt32 ;

/* Variables and functions */
 int LZMA_RESULT_OK ; 
 unsigned char* data ; 

__attribute__((used)) static int read_byte(void *object, unsigned char **buffer, UInt32 *bufferSize)
{
	*bufferSize = 1;
	*buffer = data;
	++data;
	return LZMA_RESULT_OK;
}